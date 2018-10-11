#include "GlobalVar.h"
#include "DataPackets.h"
#include "Signal.h"
#include <vector>
#include "BaseStation.h"
#include <map>
#include "Antenna.h"
#include "AreaUnit.h"
#include "Tranceivers.h"

// default constructor, does nothing but stops program from crashing
// if no information about the antenna is provided
Antenna::Antenna()
{
}

// initialize an antenna at a location (y, x) and add it to the list
// of transceivers
void Antenna::initialize(int Y, int X)
{
	this->y = Y;
	this->x = X;
	this->manifest = TranceiverList(numberOfTranceivers);
}

// set a specific location for an antenna using values of type double
void Antenna::setExactYX(double Y, double X)
{
	this->exactY = Y;
	this->exactX = X;
}

// gets values regarded the coordinate values of an antenna (y, x, exactY, exactX)
int Antenna::getY()
{
	return this->y;
}

int Antenna::getX()
{
	return this->x;
}

double Antenna::getExactY()
{
	return this->exactY;
}

double Antenna::getExactX()
{
	return this->exactX;
}

// creates a signal from data provided by (ASK ABOUT WHERE PACKETBUNDLE IS)
void Antenna::createSignalFromData(PacketBundle data)
{
	for (size_t i = 0; i < data.size(); i++)
	{ 
		Signal s(data[i]);
		this->outgoing.push_back(s);
	}
}

// adds a UserEquipment to the list of tranceivers
void Antenna::addTranceiver(UserEquipment * d)
{
	this->manifest + &(Tranceiver(d,0,0));
}

// returns the list of transceivers (the manifest)
TranceiverList Antenna::getManifest()
{
	return this->manifest;
}

/*	void setFrequencies(std::vector<int> freqs)
{
for (size_t i = 0; i < freqs.size(); i++)
{
this->frequencies.push_back(freqs[i]);
}
}*/

/*

std::vector<int> Antenna::getFrequencies()
{
	return this->frequencies;
}

void Antenna::sendSignalAcrossRegion(bool b)
{
	if (b)
	{
		for (size_t i = 0; i < regionToCover.size(); i++)
		{
			char c = regionToCover[i].sym;
			for (size_t i = 0; i < this->outgoing.getData().size(); i++)
			{
				this->outgoing.getData()[i].data = c;
			}
			env[regionToCover[i].y + this->y][regionToCover[i].x + this->x].getAppliedSignals().push_back(this->outgoing);
		}
	}
	else
	{
		for (size_t i = 0; i < regionToCover.size(); i++)
		{
			env[regionToCover[i].y + this->y][regionToCover[i].x + this->x].getAppliedSignals().push_back(this->outgoing);
		}
	}
}
*/

