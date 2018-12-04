#pragma once
#include "Table.h"
#include "TableSucces.h"

//typedef Table* Threat;

class TableThreat:public Table<TableSucces>
{
public:
	TableThreat();
	~TableThreat();
	bool getCurrentPlaying();
	int	_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};
