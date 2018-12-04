#pragma once
#include "AudioLoop.h"

class AudioLoop;

class Singleton
{
protected:
	Singleton();
	~Singleton();
	static Singleton* m_theInstance;
	static AudioLoop* m_currentlyPlaying;
public:
	static Singleton* getInstance();
    static AudioLoop* getCurrentlyPlaying();
	static void setCurrentlyPlaying(AudioLoop* currentlyplaying);
	int		_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};