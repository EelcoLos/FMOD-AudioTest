#pragma once
#include "AudioLoop.h"

class Matrix
{
private:
	vector<AudioLoop*>	cell;
	vector<int>			location;
	vector<int>			threat;
	int					locationweight;
	int					threatweight;

public:
	Matrix();
	~Matrix();

};
