#pragma once

class Mathl
{
private:
	int samplerate;
public:
	Mathl();
	~Mathl();
	double ConvertSamplesToMs(int samples);
    int ConvertMsToSamples(double ms);
	void SetSampleRate(int newsr);
	int GetSampleRate();
};
