#pragma once
#include <vector>
#include <iostream>


template <class myType>
class Table
{
protected:
	std::vector<myType*> localvector;
public:
	Table<myType>(){};
	~Table<myType>(){};

	void add(myType *yourmyTypeObject)
	{
		localvector.push_back(yourmyTypeObject);
	}

	std::vector<myType*> getVector()
	{
		return localvector;
	}
	int		_SETTEST;									// WARNING: SHOULD NOT BE USED BY ANYONE EXEPT THE (ORIGINAL) DEVELOPER
};
