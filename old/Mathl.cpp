#include "Mathl.h"

Mathl::Mathl()
{
	samplerate = 44100;
}

Mathl::~Mathl()
{
}

double Mathl::ConvertSamplesToMs(int samples)
{
	double ret;
	ret = (samples / (samples*1000));
	return ret;
}

int Mathl::ConvertMsToSamples(double ms)
{
	int ret;
	ret = (int(ms * (samplerate/1000)));
	return ret;
}

void Mathl::SetSampleRate(int newsr)
{
	samplerate = newsr;
}

int Mathl::GetSampleRate()
{
	return samplerate;
}