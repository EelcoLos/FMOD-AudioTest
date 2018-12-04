#include ".\tabley.h"

TableY::TableY(void)
{
}

TableY::~TableY(void)
{
}

vector<TableX*> TableY::getVector()
{
	if (Threat.empty())
	{
		Threat.reserve(1);
	}
	return Threat;
}

bool TableY::getCurrentPlaying()
{
	for (int i = 0; i < Threat.size(); i++)
	{
		if (Threat[i]->getCurrentPlaying())
		{
			return true;
		}
	}
	return false;
}