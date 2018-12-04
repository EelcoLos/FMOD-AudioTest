#include ".\tablex.h"

TableX::TableX()
{
}

TableX::~TableX()
{
}

vector<TableZ*> TableX::getVector()
{
	if(succession.empty())
	{
		succession.reserve(1);
	}
	return succession;
}

bool TableX::getCurrentPlaying()
{
	for (int i = 0; i < succession.size(); i++)
	{
		if (succession[i]->getCurrentPlaying())
		{
			return true;
		}
	}
	return false;
}