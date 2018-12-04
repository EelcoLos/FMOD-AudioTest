#pragma once
#include "TableY.h"

class TableY;

class TableW
{
private:
	vector<TableY*>		Location;
public:
	TableW(void);
	~TableW(void);

	vector<TableY*>		getVector();
	bool				getCurrentPlaying();
	AudioLoop*			returnCurrentPlaying();
};