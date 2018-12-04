#include "ChannelManager.h"

ChannelManager::ChannelManager()
{
	for (int i = 0; i < 1; i++)
	{
		this->channels[i] = 0;
		this->chanid[i] = 0;
	}
	
}

ChannelManager::~ChannelManager()
{
}

ChannelManager::ChannelManager(FMOD::Channel* channels[2])
{
	for (int i = 0; i <= 1; i++)
	{
		this->channels[i] = channels[i];
	}
}



int ChannelManager::FreeChannel(AudioLoop *yourAudioLoop)
{
	for (int i = 0; i <= 1; i++)
	{
		if(yourAudioLoop->getChanid() == chanid[i])
		{
			result = channels[i]->stop();
			ERRCHECK(result);
			return 1;
		}
	}
	return -1;
}

FMOD::Channel* ChannelManager::getChannel(AudioLoop *yourAudioLoop)
{
	for (int i = 0; i < 2; i++)
	{
		if(yourAudioLoop->getChanid() == chanid[i])
		{
			return channels[i];
		}
	}
	return NULL;
}

FMOD::Channel** ChannelManager::getChannelPtr(AudioLoop *yourAudioLoop)
{
	for (int i = 0; i < 2; i++)
	{
		if(yourAudioLoop->getChanid() == chanid[i])
		{
			return &channels[i];
		}
	}
	return NULL;
}

int ChannelManager::getChannelid(AudioLoop *yourAudioLoop)
{
	for (int i = 0; i < 2; i++)
	{
		if(yourAudioLoop->getChanid() == chanid[i])
		{
			return i;
		}
	}
	return -1;
}

FMOD::Channel* ChannelManager::requestChannel(AudioLoop *yourAudioLoop)
{
	if (/*this->getChannelid(yourAudioLoop)*/yourAudioLoop->getChanid() == -1)
	{
		int tempres = getFreeChannel();
		if (tempres != -1)
		{
			int rndno = rand();
			chanid[tempres] = rndno;
			yourAudioLoop->setChanID(rndno);
			return channels[tempres];
		}
	}
	return NULL;
}


int ChannelManager::getFreeChannel()
{
	for(int i = 0; i < 2; i++)
	{
		if (channels[i] == 0)
		{
			return i;
		}
	}
	return -1;
}

void ChannelManager::setChannel(AudioLoop *yourAudioLoop, FMOD::Channel *channel)
{
	channels[getChannelid(yourAudioLoop)] = channel;
}
