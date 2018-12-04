#pragma once
#include "Table.h"
#include "TableAudioLoop.h"

class TableSucces:public Table<TableAudioLoop>
{
public:
	TableSucces();
	~TableSucces();
	bool getCurrentPlaying();
	int	_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};