#include ".\mediaplayer.h"

MediaPlayer::MediaPlayer()
{
}

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::init()
{
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->getVersion(&version);
	ERRCHECK(result);

	if (FMOD_VERSION < version)
	{
		if (RETRIEVESETTEST())
		{
			std:: cerr << "This is an old version of FMOD" << std::endl;
		}
		exit(0);
	}

    result = system->init(2, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);
	memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.nonblockcallback = nonblockcallback;

	AudioChange	=	false;

	matrix = new TableLocation();
	returnresult = 0;

	//	PROCESSOR POWER OVERVIEW VARIABLES
	prevchan = nchan = 0;
	pdsp = pstream = pupdate = ptotal = cdsp = cstream = cupdate = ctotal = 0.0;
	//	/PROCESSOR POWER OVERVIEW VARIABLES
}

void MediaPlayer::update()
{

	system->update();
	if (AudioChange)
	{				
		bool getchannelpaused = false;
        
		int getchannelsplaying = 0;
		result = system->getChannelsPlaying(&getchannelsplaying);
		ERRCHECK(result);
		
		if (getchannelsplaying > 0)
		{
			if (!matrix->returnCurrentPlaying()->getbeentroughCurrentUpdate())
			{
				returnresult = matrix->returnCurrentPlaying()->getCurrentLocationReference();
				pending->LoadSound(system);
			}
			if (matrix->returnCurrentPlaying()->updatePosition(pending, returnresult) == 1) 
			{	
				AudioChange = false;
			}
			/*else if (matrix->returnCurrentPlaying()->updatePosition(pending, returnresult) == 3)
			{
				AudioChange = false;
				this->InsertAudio(location_number, threat_number, succes_number);
			}*/
		}
		else
		{		
			unsigned int percentbuffed;
			FMOD_OPENSTATE status;
			bool starving;
			pending->LoadSound(system);

			//play chosen channel
			FMOD::Channel *tempchan = NULL;
			result = pending->getSound()->getOpenState(&status, &percentbuffed, &starving);
			ERRCHECK(result);

			if (status == FMOD_OPENSTATE_READY)
			{
				pending->Play(NULL);
				Singleton::setCurrentlyPlaying(pending);
				AudioChange = false;
			}
			else
			{
				if (RETRIEVESETTEST())
				{
					std::cout << "percentage loaded: " << percentbuffed << std::endl;
				}
			}
		}
	}
	else
	{
		int getchannelsplaying = 0;
		result = system->getChannelsPlaying(&getchannelsplaying);
		ERRCHECK(result);
		if (getchannelsplaying > 0)
		{
			if(matrix->returnCurrentPlaying()->getCurrentPosition() >= (matrix->returnCurrentPlaying()->getSoundLength() - 176400))
			{

				AudioChange = false;
				InsertAudio(location_number, threat_number, succes_number);
			}
		}
	}

	Sleep(10);
	prevchan = nchan;
	result = system->getChannelsPlaying(&nchan);
	ERRCHECK(result);
	if (nchan != prevchan)
	{
		if (RETRIEVESETTEST())
		{
			std::cout << "Number of channels playing CHANGED!!! Current number of channels playing: " << nchan << std::endl;
		}
	}	
	
	pdsp = cdsp;
	pstream = cstream;
	pupdate = cupdate;
	ptotal = ctotal;
	result = system->getCPUUsage(&cdsp, &cstream, &cupdate, &ctotal);
	ERRCHECK(result);

	if ((ctotal - ptotal) >= 0.3 )
	{
		if (RETRIEVESETTEST())
		{
			std::cout << std::setprecision(2) <<  "current CPU usage: DSP: " << cdsp << "%, Stream: " << cstream 
				<< "%, Update: "<< cupdate << "%,  Total :" << ctotal << "%"<< std::endl;
		}
	}	
}


void MediaPlayer::InsertAudio(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber, unsigned int AudioLoopnumber)
{
	pending = matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->getVector()[succes_vnumber]->getVector()[AudioLoopnumber];
	AudioChange = true;
}
void MediaPlayer::InsertAudio(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber)
{
	pending = matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->getVector()[succes_vnumber]->ChooseAudioLoopfromVector();
	if (RETRIEVESETTEST())
	{
		std::cout << "MediaPlayer::InserAudio(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber) return the following AudioLoop: " << pending->getFileName() << std::endl;
	}
	AudioChange = true;
}

void MediaPlayer::quit()
{
	system->close();
	exit(0);
}

void MediaPlayer::InsertFile(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber, char* AudioLoopFilename, std::vector<int> *breakpoints)
{
	location_number		= location_vnumber;
	threat_number		= threat_vnumber;
	succes_number		= succes_vnumber;
	if (matrix->getVector().size() < (location_vnumber+1))
	{
		while(matrix->getVector().size() <= location_vnumber)
		{
			matrix->add(new TableThreat());
		}
	}
	else if (matrix->getVector()[location_vnumber]->getVector().size() < (threat_vnumber+1))
	{
		while(matrix->getVector()[location_vnumber]->getVector().size() <= threat_vnumber)
		{
			matrix->getVector()[location_vnumber]->add(new TableSucces());
		}
	}
	else if (matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->getVector().size() < (succes_vnumber+1))
	{
		while(matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->getVector().size() <= succes_vnumber)
		{
			matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->add(new TableAudioLoop());
		}
	}
	AudioLoop *test = new AudioLoop(AudioLoopFilename, 6, 44100, *breakpoints, system);

	matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->getVector()[succes_vnumber]->add(test);
	matrix->getVector()[location_vnumber]->getVector()[threat_vnumber]->getVector()[succes_vnumber]->_SETTEST = 0;
}

TableLocation* MediaPlayer::getMatrix()
{
	return matrix;
}

void MediaPlayer::SETTEST(int newtestvariable)
{
	this->_SETTEST = 0;
	matrix->_SETTEST = 0;
	for (unsigned int i = 0; i < matrix->getVector().size(); i++)
	{
		for (unsigned int k = 0; k < matrix->getVector()[i]->getVector().size(); k++)
		{
			for (unsigned int l = 0; l <matrix->getVector()[i]->getVector()[k]->getVector().size(); l++)
			{
				for (unsigned int m = 0; m < matrix->getVector()[i]->getVector()[k]->getVector()[l]->getVector().size(); m++)
				{
					matrix->getVector()[i]->getVector()[k]->getVector()[l]->getVector()[m]->_SETTEST = 0;
				}
				matrix->getVector()[i]->getVector()[k]->getVector()[l]->_SETTEST = 0;
			}
			matrix->getVector()[i]->getVector()[k]->_SETTEST = 0;
		}
		matrix->getVector()[i]->_SETTEST = 0;
	}
}
int MediaPlayer::RETRIEVESETTEST()
{
	return _SETTEST;
}