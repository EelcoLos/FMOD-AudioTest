#include ".\tablelocation.h"


TableLocation::TableLocation()
{
	add(new TableThreat);
}

TableLocation::~TableLocation()
{
}

bool TableLocation::getCurrentPlaying()
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

AudioLoop* TableLocation::returnCurrentPlaying()
{
	return Singleton::getInstance()->getCurrentlyPlaying();
}