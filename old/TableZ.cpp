#include ".\tablez.h"

TableZ::TableZ(void)
{
}

TableZ::~TableZ(void)
{
}

vector<AudioLoop*> TableZ::getAudioLoopVector()
{
	if (audioloops.empty())
	{
		audioloops.reserve(1);
	}
	return audioloops;
}

void TableZ::addAudioLoop(char *filename, int maxnumberofrepeats, vector<int> breakpoints)
{
	AudioLoop *temp = new AudioLoop(filename, maxnumberofrepeats, 44100, breakpoints);
	audioloops.push_back(temp);
}

void TableZ::addAudioLoop(AudioLoop *yourAudioLoop)
{
	audioloops.push_back(yourAudioLoop);
}

AudioLoop* TableZ::ChooseAudioLoopfromVector()
{
	return AudioChooser->AudioLoopChoose(audioloops);
}

bool TableZ::getCurrentPlaying()
{
	for (int i = 0; i < audioloops.size(); i++)
	{
		if (audioloops[i]->getChannel())
		{
			return true;
		}
	}
	return false;
}
