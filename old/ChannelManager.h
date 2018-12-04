#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Mathl.h"
#include "AudioLoop.h"
#include "resource.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <vector>


class ChannelManager
{
private:
	FMOD::Channel*		channels[2];
	int					chanid[2];
	FMOD_RESULT			result;
	
	int					getFreeChannel();
public:
	ChannelManager();
	~ChannelManager();
	ChannelManager(FMOD::Channel* channels[2]);
	
	FMOD::Channel*		getChannel(AudioLoop *yourAudioLoop);
	FMOD::Channel**		getChannelPtr(AudioLoop *yourAudioLoop);
	int					FreeChannel(AudioLoop *yourAudioLoop);
	int					getChannelid(AudioLoop *yourAudioLoop);
	FMOD::Channel*		requestChannel(AudioLoop *yourAudioLoop);
	void				setChannel(AudioLoop *yourAudioLoop, FMOD::Channel* channel);
};
