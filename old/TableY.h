#pragma once
#include "TableX.h"

class TableX;

class TableY
{
private:
	vector<TableX*> Threat;
public:
	TableY(void);
	~TableY(void);

	vector<TableX*>	getVector();
	bool			getCurrentPlaying();
};
