#include "audioloop.h"

int		AudioLoop::maxnumberofrepeats		=	0;

AudioLoop::AudioLoop()
{
	this->init();
}

AudioLoop::~AudioLoop()
{
}
AudioLoop::AudioLoop(char *filename, int maxnumberofrepeats, int crossfadetime, std::vector<int> breakpoints, FMOD::System *system)
{
	this->init();
	setdata(filename, maxnumberofrepeats, crossfadetime, breakpoints, system);
}

FMOD::Sound* AudioLoop::LoadSound(FMOD::System *sys)
{
	//if (!sound)
	//{
	result = sys->createStream(filename, /*FMOD_NONBLOCKING*/FMOD_DEFAULT, 0, &sound);
	ERRCHECK(result);
	//}
	return sound;
}

void AudioLoop::init()
{
	strcpy(filename, "");
	maxnumberofrepeats			=	0;
	channel						=	0;
	numberoftimesplayed			=	0;
	channelid					=	-1;
	channelcrossfadetime		=	44100;
	channelpaused				=	false;
	beentroughCrossFadeOnce		=	false;
	beentroughCurrentUpdate		=	false;
	sound						=	0;
	channel						=	0;
	//breakpoint				=	0;
	//beentroughLoadSound		=	false;
	//soundloaded				=	false;
	//soundavailable			=	false;
	//channelavailable			=	false;
	percentageloaded			=	0;
	delaytime					=	44100;/*176400;		// 4 seconds @ 44100 SR!*/
	currentlyplaying			=	false;
	
	
	_SETTEST					=	0;
}

void AudioLoop::setdata(char *newfilename, int maxnumberofrepeats, int crossfadetime, std::vector<int> breakpoints,FMOD::System *system)
{
	strcpy(filename, newfilename);
	if (_SETTEST)
	{
		std::cout << "FILENAME!: " << newfilename << std::endl;
		std::cout << "AudioLoop::setdata(char *newfilename, int maxnumberofrepeats, int crossfadetime, std::vector<int> breakpoints, FMOD::System *system) has filename: " << filename << std::endl;
	}
	this->maxnumberofrepeats	=	maxnumberofrepeats;
	this->channelcrossfadetime	=	crossfadetime;
	this->breakpoints			=	breakpoints;
	this->sys					=	system;
}

int AudioLoop::getCurrentLocationReference()
{
	if (!beentroughCurrentUpdate)
	{
		unsigned int position, length = 0;
		
		result = channel->getPosition(&position, FMOD_TIMEUNIT_PCM);
		ERRCHECK(result);

		result = sound->getLength(&length, FMOD_TIMEUNIT_PCM);
		ERRCHECK(result);

		for (std::vector<int>::const_iterator i = breakpoints.begin(); i != breakpoints.end(); i++)
		{
			if (((unsigned int)*i) > (position + delaytime)) {
				beentroughCurrentUpdate = true;
				return *i;
			}
		}
		beentroughCurrentUpdate = true;
		return length;
	}
	return NULL;
}
int AudioLoop::updatePosition(AudioLoop *otherfile, unsigned int breakpoint)
{
	unsigned int position = 1;
	result = channel->getPosition(&position, FMOD_TIMEUNIT_PCM);
	ERRCHECK(result);
	
	//FMOD::System *tempsys;
	FMOD_OPENSTATE state = FMOD_OPENSTATE_LOADING;
	if(otherfile->getSound())
	{
		result = otherfile->getSound()->getOpenState(&state, 0,0);
		ERRCHECK(result);
	}

	if (position >= breakpoint)
	{
		if (!beentroughCrossFadeOnce)
		{
			if (_SETTEST)
			{
				std::cout << "Position for crossfading reached/passed!" << std::endl;
			}
		}
		return Crossfade(otherfile);
	}

	unsigned int length = 0;
	result = sound->getLength(&length, FMOD_TIMEUNIT_PCM);
	ERRCHECK(result);
	if (position >= (length - (delaytime*2)))
	{
		/*if (otherfile)
		{
			return Crossfade(otherfile);
		}
		return Crossfade(NULL);*/
		return 3;
	}
	return false;
}

FMOD::Channel* AudioLoop::getChannel()
{
	return channel;
}

FMOD::Sound* AudioLoop::getSound()
{
	if (sound)
	{
		return sound;
	}
	return LoadSound(sys);
	if (_SETTEST)
	{
		std:: cerr << "There is no Sound available. Use AudioLoop::LoadSound(FMOD::System *sys) to load a sound." << std::endl;
	}
	return NULL;
}

bool AudioLoop::Crossfade(AudioLoop *otherfile)
{
	float channelvolume;
	bool b;
	if (this != otherfile)							// this is very dirty code, but it seemed that files which will be played
	{												// recursive are not being crossfaded correctly.
		if (!beentroughCrossFadeOnce)
		{
			setChannelVolume(1.0);
			otherfile->Play(this);
			//otherfile->setChannelPaused(false);
			beentroughCrossFadeOnce = true;
			numberoftimesplayed++;
		}

		result = channel->getVolume(&channelvolume);
		ERRCHECK(result);
		
		channelvolume *= (float)0.9;
		if (_SETTEST)
		{
			std::cout << "Volume van spelend file: " << channelvolume << std::endl;
		}
		result = channel->setVolume(channelvolume);
		ERRCHECK(result);
		otherfile->setChannelVolume((float)1.0 - channelvolume);
		if (_SETTEST)
		{
			std::cout << "Volume van pending file: " << otherfile->getChannelVolume() << std::endl;
		}

		if (b = (getChannelVolume() <= 0.01))
		{
			otherfile->setChannelVolume(1.0);
			Singleton::setCurrentlyPlaying(otherfile);
			channel->setPaused(true);
			this->Stop();
		}
		return b;
	}
	else if (this == otherfile)
	{
		FMOD::Sound		*tempsnd;
		FMOD::Channel	*tempchan;
		FMOD_OPENSTATE	tempstate;
		tempsnd = otherfile->getSound();
		//result = sys->createSound(otherfile->getFileName(), FMOD_NONBLOCKING, 0, &tempsnd);
		//ERRCHECK(result);
		result = sys->playSound(FMOD_CHANNEL_FREE, tempsnd, false, &tempchan);
		ERRCHECK(result);
		if (b = (getChannelVolume() <= 0.01))
		{
			result = tempchan->setVolume(1.0);
			channel->setPaused(true);
			this->Stop();
			this->setChannel(tempchan);
		}
		
	}
}

bool AudioLoop::getPausedChannel()
{
	result = channel->getPaused(&channelpaused);
	ERRCHECK(result);
	return							channelpaused;
}

bool AudioLoop::getbeentroughCrossFadeOnce()
{
	return							beentroughCrossFadeOnce;
}

bool AudioLoop::getbeentroughCurrentUpdate()
{
	return							beentroughCurrentUpdate;
}

float AudioLoop::getChannelVolume()
{
	if (channel) {
		float volume;
		result = channel->getVolume(&volume);
		ERRCHECK(result);
		return volume;
	}
	return 0.0;
}

char* AudioLoop::getFileName()
{
	return filename;
}

bool AudioLoop::getSoundLoaded()
{
	FMOD_OPENSTATE status;
	if (sound)
	{
		result = sound->getOpenState(&status, &percentageloaded, 0);
		ERRCHECK(result);
		if (status == FMOD_OPENSTATE_READY)
		{
			return true;
		}
	}
	return false;
}

int AudioLoop::getPercentageLoaded()
{
	FMOD_OPENSTATE status;
	result = this->sound->getOpenState(&status, &percentageloaded, 0);
	ERRCHECK(result);
	return percentageloaded;
}

int AudioLoop::getNumberoftimesplayed()
{
	return numberoftimesplayed;
}

bool AudioLoop::getRecentlyPlayed()
{
	return recentlyplayed;
}

int AudioLoop::getNumbermaxtimeplay()
{
	return maxnumberofrepeats;
}

int AudioLoop::getDelayTime()
{
	return delaytime;
}

void AudioLoop::setbeentroughCrossFadeOnce(bool truefalse)
{
	beentroughCrossFadeOnce		=	truefalse;
}

void AudioLoop::setbeentroughCurrentUpdate(bool truefalse)
{
	beentroughCurrentUpdate		=	truefalse;
}

void AudioLoop::setChannelPaused(bool truefalse)
{
	result						=	channel->setPaused(truefalse);
	ERRCHECK(result);
}

void AudioLoop::setChannelVolume(float newvolume)
{
	result						=	channel->setVolume(newvolume);
	ERRCHECK(result);
}


void AudioLoop::setChannel(FMOD::Channel *newchan)
{
	channel = newchan;
	if (sound && channel)
	{
		recentlyplayed = true;
	}
}

void AudioLoop::addNumberoftimeplayed()
{
	numberoftimesplayed++;
}

void AudioLoop::addNumberoftimeplayed(int addition)
{
	numberoftimesplayed += addition;
}

void AudioLoop::setRecentlyPlayed(bool truefalse)
{
	if (truefalse != recentlyplayed)
	{
		recentlyplayed = truefalse;
	}
}

void AudioLoop::setDelaytime(int newdelaytime)
{
	delaytime = newdelaytime;
}

void AudioLoop::Play(AudioLoop *currentlyPlaying)
{
	int getchanplaying;
	if (!channel)
	{
		FMOD_OPENSTATE status;
		if (!sound)
		{
			LoadSound(sys);
		}

		if (getChannelsPlaying() > 1)
		{
			unsigned int breakpoint = 0;
			if (currentlyPlaying)
			{
				if (!currentlyPlaying->getbeentroughCurrentUpdate())
				{
					breakpoint = currentlyPlaying->getCurrentLocationReference();
				}
				if (currentlyPlaying->updatePosition(this, breakpoint))
				{
					currentlyPlaying->Stop();
				}
			}
		}
		else if(getChannelsPlaying() == -1)
		{
			std::cout << "Cannot retrieve Channels loading!" << std::endl;
		}
		else
		{
			if (getSoundLoaded())
			{
				result = sys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
				ERRCHECK(result);
				currentlyplaying = true;
			}
			else
			{
				if (_SETTEST)
				{
					std::cout << "percentage loaded: " << getPercentageLoaded() << std::endl;
				}
			}
		}
	}
	else if(sound && channel)
	{
		result = channel->setPaused(false);
		ERRCHECK(result);
		currentlyplaying = true;
		Singleton::setCurrentlyPlaying(this);
	}
	else
	{
		if (_SETTEST)
		{
			std:: cerr << "Can't play atm check your flow of start - end" << std::endl;
		}
	}
}

void AudioLoop::Stop()
{
	if (channel)
	{
		
		beentroughCrossFadeOnce = false;
		beentroughCurrentUpdate = false;

		result = channel->setPaused(true);
		ERRCHECK(result);
		
		result = channel->stop();
		ERRCHECK(result);
		
		result = sound->release();
		ERRCHECK(result);

		channel = 0;
		currentlyplaying = false;
	}
	else
	{
		if(_SETTEST)
		{
			std::cout << "Error can't find channel, this AudioLoop is not playing yet!" << std::endl;
		}
	}
}

int AudioLoop::getChannelsPlaying()
{
	FMOD::System *sys;
	int nochan;
	if (sound)
	{
		result = sound->getSystemObject(&sys);
		ERRCHECK(result);

		result = sys->getChannelsPlaying(&nochan);
		ERRCHECK(result);
		return nochan;
	}
	return -1;
}

bool AudioLoop::getCurrentlyPlaying()
{
	return currentlyplaying;
}

int AudioLoop::getSoundLength()
{
	unsigned int length = 0;
	result = sound->getLength(&length, FMOD_TIMEUNIT_PCM);
	ERRCHECK(result);
	return length;
}

int AudioLoop::getCurrentPosition()
{
	unsigned int position = 0;
	result = channel->getPosition(&position, FMOD_TIMEUNIT_PCM);
	ERRCHECK(result);
	return position;
}