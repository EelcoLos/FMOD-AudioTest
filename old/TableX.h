#pragma once
#include "TableZ.h"

class TableZ;

class TableX
{
private:
	vector<TableZ*> succession;
public:
	TableX();
	~TableX();

	vector<TableZ*>	getVector();
	bool			getCurrentPlaying();
};
