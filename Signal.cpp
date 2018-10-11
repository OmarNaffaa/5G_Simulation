#include "DataPackets.h"
#include "Signal.h"

// Consrtuctor
Signal::Signal(Packet data)
	{
		this->signalStrength = 0;
		this->frequency = 0;
		this->data = data;
	}

// Setters for various aspects of the signal
// (strength, frequency, and data being transferred)
void Signal::setSignalStrength(int sStren)
{
	this->signalStrength = sStren;
}

void Signal::setFrequency(int freq)
{
	this->frequency = freq;
}

void Signal::setData(Packet dat)
{
	this->data = dat;
}

// Getters for various aspects of the signal
// (strength, frequency, and data being transferred)
int Signal::getSignalStrength()
{
	return this->signalStrength;
}

int Signal::getFrequency()
{
	return this->frequency;
}

Packet Signal::getData()
{
	return this->data;
}
