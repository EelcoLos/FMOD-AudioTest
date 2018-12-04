#include ".\tablesucces.h"

TableSucces::TableSucces()
{
	this->add(new TableAudioLoop());
}

TableSucces::~TableSucces()
{}

bool TableSucces::getCurrentPlaying()
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
