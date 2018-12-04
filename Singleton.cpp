#include ".\singleton.h"

Singleton* Singleton::m_theInstance = 0;
AudioLoop* Singleton::m_currentlyPlaying = 0;


Singleton::Singleton()
{}

Singleton::~Singleton()
{}

Singleton* Singleton::getInstance()
{
	if (m_theInstance)
	{
		m_theInstance = new Singleton();
	}
	return m_theInstance;

}

AudioLoop* Singleton::getCurrentlyPlaying()
{
	/*if (m_currentlyPlaying)
	{
		return NULL;
	}
	else
	{*/
		return m_currentlyPlaying;
}

void Singleton::setCurrentlyPlaying(AudioLoop* currentlyplaying)
{
	m_currentlyPlaying = currentlyplaying;
}