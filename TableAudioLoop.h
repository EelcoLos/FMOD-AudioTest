#pragma once
#include "Table.h"
#include "AudioLoop.h"
#include "AudioLoopChooser.h"

class TableAudioLoop:public Table<AudioLoop>
{
public:
	TableAudioLoop();
	~TableAudioLoop();
	AudioLoop*	ChooseAudioLoopfromVector();
	bool getCurrentPlaying();
	int		_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};
