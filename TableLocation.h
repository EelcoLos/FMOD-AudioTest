#pragma once
#include "Table.h"
#include "TableThreat.h"
#include "Singleton.h"

//typedef Table* Location;

class TableLocation:public Table<TableThreat>
{
public:
	TableLocation();
	~TableLocation();
	bool getCurrentPlaying();
	AudioLoop* returnCurrentPlaying();
	int		_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};
