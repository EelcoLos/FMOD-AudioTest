#include "fmod.hpp"
/*
//	AudioLoop Class
//	Building a wrapper class for Far Cry to CrossFade with control to the programmer
//	Built by: Eelco Los
//	Last Update: 18-01-2007
*/

#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include "errfunc.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <vector>
#include "Singleton.h"

#include <iostream>



class AudioLoop
{	
private:
	//Channel properties
//	FMOD::Channel *channel;
//	FMOD::System *sys;
	int						channelid;
	bool					channelpaused;
	//float					channelvolume;
	int						channelcrossfadetime;
	
	//Sound properties
//	FMOD::Sound *sound;
	char					filename[255];
	static int				maxnumberofrepeats;
	int						numberoftimesplayed;
	bool					recentlyplayed;
	
	std::vector<int>		breakpoints;
	FMOD_RESULT				result;
	bool					beentroughCrossFadeOnce;
	bool					beentroughCurrentUpdate;
	//bool					beentroughLoadSound;
	//bool					soundloaded;
	//bool					soundavailable;				// Checking if there is a sound in this AudioLoop
	//bool					channelavailable;			// Checking if there is a channel in this AudioLoop
	unsigned int			percentageloaded;
	int						delaytime;
	bool					currentlyplaying;
	//unsigned int			breakpoint;

protected:

public:

	//constuctor & destructors
	AudioLoop();
	~AudioLoop();
AudioLoop(char *filename, int maxnumberofrepeats, int crossfadetime, std::vector<int> breakpoints, FMOD::System *system);
	
	void init();

	FMOD::Sound* LoadSound(FMOD::System *sys);
	
	//inits etc
	void setdata(char *filename, int maxnumberofrepeats, int crossfadetime, std::vector<int> breakpoints,FMOD::System *system);

	//functions
	int getCurrentLocationReference();
	int updatePosition(AudioLoop *otherfile, unsigned int breakpoint);
	bool Crossfade(AudioLoop *otherfile);
	void Play(AudioLoop *currentlyPlaying);
	void Stop();

    //retrieve functions    
	FMOD::Channel*		getChannel();
	FMOD::Sound*		getSound();
	char*				getFileName();
	bool				getPausedChannel();
	bool				getbeentroughCrossFadeOnce(); 
	bool				getbeentroughCurrentUpdate();
	float				getChannelVolume();
	bool				getSoundLoaded();
	int					getPercentageLoaded();
	int					getNumberoftimesplayed();
	int					getNumbermaxtimeplay();
	bool				getRecentlyPlayed();
	int					getDelayTime();
	int					getChannelsPlaying();
	bool				getCurrentlyPlaying();
	int					getSoundLength();
	int					getCurrentPosition();
	

	void				setbeentroughCrossFadeOnce(bool truefalse);
	void				setbeentroughCurrentUpdate(bool truefalse);
	void				setChannelPaused(bool truefalse);
	void				setChannelVolume(float newvolume);
	void				setChannel(FMOD::Channel* newchan);
	void				addNumberoftimeplayed();
	void				addNumberoftimeplayed(int addition);
	void				setRecentlyPlayed(bool truefalse);
	void				setDelaytime(int newdelaytime);

	int					_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
private:
	// Channel properties
	FMOD::Channel *channel;
	FMOD::System *sys;
	// Sound properties
	FMOD::Sound *sound;
};
