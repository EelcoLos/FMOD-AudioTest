#include "audioloopchooser.h"

AudioLoopChooser::AudioLoopChooser()
{
	_SETTEST = 0;
}

AudioLoopChooser::~AudioLoopChooser()
{
}

AudioLoop* AudioLoopChooser::AudioLoopChoose(std::vector<AudioLoop*> yourAudioLoopvector)
{
	AudioLoop *tempresult = choose(yourAudioLoopvector);
	if (_SETTEST)
	{
		std::cout << "AudioLoop INFO\n-----------------------------\nFilename:\t" << tempresult->getFileName() << std::endl << "sound available:\t" << tempresult->getSound() << std::endl;
	}

	while (Singleton::getCurrentlyPlaying() == tempresult)
	{
		tempresult = choose(yourAudioLoopvector);
	}
	/*if(tempresult->getRecentlyPlayed())						// 
	{
	
	}
	int tempmaxplay = tempresult->getNumbermaxtimeplay();
	int tempnotplayed = tempresult ->getNumberoftimesplayed();
	if(tempresult->getNumbermaxtimeplay())
	{
		
	}*/
	return tempresult;
}