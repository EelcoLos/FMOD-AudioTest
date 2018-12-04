/*
//	MediaPlayer
//	Controlling Initialisation and Updating of Matrix & AudioLoops for Far Cry
//	Created By: Eelco Los
//	Last Update: 19-01-2007
*/

#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include "AudioLoop.h"
#include "AudioLoopChooser.h"
#include "TableLocation.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <vector>

#include <iostream>
#include <iomanip>


FMOD_RESULT static F_CALLBACK nonblockcallback(FMOD_SOUND *sound, FMOD_RESULT result)
{
    FMOD::Sound *snd = (FMOD::Sound *)sound;

    printf("Sound loaded! (%d) %s\n", result, FMOD_ErrorString(result)); 

    return FMOD_OK;
}

class MediaPlayer
{
private:
	FMOD::System *system;													// FMOD System													
	FMOD_RESULT				result;														// FMOD's own resulter. Depricates Null-pointer crashes
	int						key;														// integer for storing key numbers which are hitted
	int						buffrange;													// Loose integer to store random number for initialisation FMOD
	unsigned int			version;													// FMOD Version Checker
	FMOD_CREATESOUNDEXINFO	exinfo;														// FMOD info in own type of structure
	TableLocation			*matrix;													// Matrix consisting out of tables.
	AudioLoop*				pending;													// pending AudioLoop
	char					zooibuff[255];												// Loose char array to store random stuff for initialiation FMOD
	int						prevchan, nchan;											// Information variables
	float					pdsp , pstream , pupdate , ptotal , cdsp , cstream , cupdate , ctotal;	// Information variables

	unsigned int			location_number, threat_number, succes_number;				// Table numbers used to check if at the end of a file to pick another file from same zone

	
	std::vector<int>		*breakpoints;												//maybe removed soon because of farcry integration!
	
	bool					AudioChange;												// Checking if there is a call for Audio Changing
	int						returnresult;												// own variable to check nearest breakpoint for breaking audioloop
public:
	MediaPlayer();																		// Constructor
	~MediaPlayer();																		// Destructor

	void					init();														// Initialising function. MUST BE USED
	void					update();													// Update loop
	void					quit();														// For Quitting the program
	void					InsertAudio(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber, unsigned int AudioLoopnumber);	// Selecting an audioloop for playing. Not working or bugged
	void					InsertAudio(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber);								// Selecting a zone, choosing a random audioloop from it to play.
	void					InsertFile(unsigned int location_vnumber, unsigned int threat_vnumber, unsigned int succes_vnumber, char* AudioLoopFileName, std::vector<int> *breakpoints);	// Inserting File data and location where it should be stored.
	TableLocation*			getMatrix();												// Returns the entire matrix. Should be used for developing only.
	int						_SETTEST;													// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
	void					SETTEST(int newtestvariable);								// Setting the _SETTEST variable
	int						RETRIEVESETTEST();											// Returning _SETTEST variable
};