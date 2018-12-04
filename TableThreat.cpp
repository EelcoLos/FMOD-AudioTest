#include ".\tablethreat.h"

TableThreat::TableThreat()
{
	localvector.push_back(new TableSucces());
}

TableThreat::~TableThreat()
{
}

bool TableThreat::getCurrentPlaying()
{
	for (unsigned int i = 0; i < localvector.size(); i++)
	{
		if (localvector[i]->getCurrentPlaying())
		{
			return true;
		}
	}
	return false;
}
