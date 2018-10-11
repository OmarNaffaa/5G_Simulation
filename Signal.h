#pragma once
//#include <vector>

class Packet;


class Signal
{
protected:
	int signalStrength;
	int frequency;
	Packet data;
public:

	Signal(Packet data);

	void setSignalStrength(int sStren);

	void setFrequency(int freq);

	void setData(Packet dat);

	int getSignalStrength();

	int getFrequency();

	Packet getData();
};

// defines the type of a vector of signals as Signals
typedef std::vector<Signal> Signals;