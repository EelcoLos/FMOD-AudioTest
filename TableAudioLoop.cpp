#include ".\tableaudioloop.h"

TableAudioLoop::TableAudioLoop()
{
	//localvector.push_back(new AudioLoop());
}

TableAudioLoop::~TableAudioLoop()
{
}

AudioLoop* TableAudioLoop::ChooseAudioLoopfromVector()
{
	AudioLoopChooser *chooser = new AudioLoopChooser();
	AudioLoop *test = chooser->AudioLoopChoose(localvector);
	if (_SETTEST)
	{
		std::cout << "ChooseAudioLoopFromVector(): called for and filename is: " << test->getFileName() << std::endl;
	}
	return test;
}

bool TableAudioLoop::getCurrentPlaying()
{
	for(unsigned int i = 0; i < localvector.size(); i++)
	{
		if (localvector[i]->getCurrentlyPlaying())
		{
			return true;
		}
	}
	return false;
}