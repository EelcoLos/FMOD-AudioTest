#pragma once
#include "Chooser.h"
#include "AudioLoop.h"

class AudioLoopChooser:public Chooser<AudioLoop>
{
private:
	bool ignorerecentlyplayed;
	int playedweighingfactor;
public:
	AudioLoopChooser();
	~AudioLoopChooser();

	AudioLoop* AudioLoopChoose(std::vector<AudioLoop*> yourAudioLoopvector);

	int	_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};
