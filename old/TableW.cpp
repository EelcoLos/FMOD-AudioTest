#include ".\tablew.h"

TableW::TableW(void)
{
}

TableW::~TableW(void)
{
}

vector<TableY*> TableW::getVector()
{
	if (Location.empty())
	{
		Location.reserve(1);
	}
	return Location;
}

bool TableW::getCurrentPlaying()
{
	for (int i = 0; i < Location.size(); i++)
	{
		if (Location[i]->getCurrentPlaying())
		{
			return true;
		}
	}
	return false;
}

AudioLoop* TableW::returnCurrentPlaying()
{
	for (int i = 0; i < Location.size(); i++)
	{
		if (Location[i]->getCurrentPlaying())
		{
			for (int j = 0; j < Location[i]->getVector().size(); j++)
			{
				if (Location[i]->getVector()[j]->getCurrentPlaying())
				{
					for(int k = 0; k < Location[i]->getVector()[j]->getVector().size(); k++)
					{
						if (Location[i]->getVector()[j]->getVector()[k]->getCurrentPlaying())
						{
							for(int l = 0; l < Location[i]->getVector()[j]->getVector()[k]->getAudioLoopVector().size(); l++)
							{
								if (Location[i]->getVector()[j]->getVector()[k]->getAudioLoopVector()[l]->getChannel())
								{
									return Location[i]->getVector()[j]->getVector()[k]->getAudioLoopVector()[l];
								}
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}