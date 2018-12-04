#pragma once
#include "AudioLoop.h"
#include "AudioLoopChooser.h"

class AudioLoop;

class TableZ
{
private:
	vector<AudioLoop*>	audioloops;
	AudioLoopChooser	*AudioChooser;
public:
	TableZ(void);
	~TableZ(void);

	vector<AudioLoop*>	getAudioLoopVector();
	void				addAudioLoop(char *filename, int maxnumberofrepeats, vector<int> breakpoints);
	void				addAudioLoop(AudioLoop *yourAudioLoop);
	AudioLoop*			ChooseAudioLoopfromVector();
	bool				getCurrentPlaying();
};
