#pragma once
#include "AudioLoop.h"
#include <vector>
#include <iostream>
#include <time.h>


template <class myType>
class Chooser
{
protected:
	std::vector<myType*>		personalVector;

public:
	Chooser<myType>(){};
	~Chooser<myType>(){};

	myType*		choose(std::vector<myType*> yourmyTypevector)
	{
		personalVector = yourmyTypevector;
		srand((unsigned int)time(NULL));
		return yourmyTypevector[(rand() % (yourmyTypevector.size()/*-1*/))];
	};
	void		rem(int vectorid)
	{

	};

	int	_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};