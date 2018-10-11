#pragma once
#include "BaseStation.h"
#include <math.h>

#define PI 3.14159265

BaseStation::BaseStation()
{
}

BaseStation::BaseStation(int y, int x, int objcnt)
{
	this->objID = objcnt;
	this->setYX(y, x);
	this->maxBandwith = 5 * numberOfTranceivers;
}


void BaseStation::InitializeDefaults(int y, int x, int objcnt)
{
	this->objID = objcnt;
	this->setYX(y, x);
	this->maxBandwith = 5*numberOfTranceivers;

	double exactY = this->y + 0.5;
	double exactX = this->x + 0.5;
	double radius = 0.5;
	double degreesToRadians = PI / 180;
	double degreeSeparation = 360 / numberOfAntenna;

	this->MIMOs = new Antenna[numberOfAntenna];

	for (int A = 0; A < numberOfAntenna; A++)
	{
		this->MIMOs[A].initialize(this->y, this->x); // IS MIMOs THE LIST OF ANTENNAS CREATED
		double angle = A*degreeSeparation;
		double antennaExactY = radius*sin(degreesToRadians*angle);
		double antennaExactX = radius*cos(degreesToRadians*angle);
		this->MIMOs[A].setExactYX(antennaExactY + exactY, antennaExactX + exactX);
	}
}

void BaseStation::addToRegion(int y, int x)
{
	Point n(y, x);
	this->region.push_back(n);
}

Point& BaseStation::operator[] (int x) {
	return this->region[x];
}

int BaseStation::getRegionSize()
{
	return this->region.size();
}

Antenna* BaseStation::getAntennaList()
{
	return this->MIMOs;
}

void BaseStation::setObjID(int id) 
{
	this->objID = id;
}

void BaseStation::setYX(int Y, int X )
{
	this->y = Y;
	this->x = X;
}
void BaseStation::setMaxBandwith(int n)
{
	this->maxBandwith = n;
}

int BaseStation::getObjID()
{
	return this->objID;

}
int BaseStation::getX()
{
	return this->x;

}
int BaseStation::getY()
{
	return this->y;

}
int BaseStation::getMaxBandwith()
{
	return this->maxBandwith;

}

PacketBundle BaseStation::getIncomingBuffer()
{
	return this->incomingBuffer;
}

PacketBundle BaseStation::getOutgoingBuffer()
{
	return this->outgoingBuffer;
}

BaseStation* BaseStation::getPointer()
{
	return (this);
}


void BaseStation::sendOutgoingBuffer(PacketBundle Outgoing)
{
}

bool BaseStation::Update()
{
	/*
	for each antenna in MIMOs
	{
		for each tranceiver in tranceiverList    <-iterator!
		{
			get the objID of the cellular device,
			then use the iterator that indicates the tranceiver:
			create packet like using the constructor: Packet(int sendr, int destin);
			use the tranceiver iterator as the sender and the objID as the destination.
			add the packet to the outgoingBuffer
		}
		then call createSignaFromData(outgoingBuffer)
		then go through each signal in outgoing and use the sender in the packet so you know which tranceiver has the pointer to the correct ceullular device.
		then use the pointer to add the signal to the cellular device incomingsignals buffer.
	}
	*/

	// iterates through each all the antennas in a BaseStation
	// (BaseStations are iterated through in the main class
	for (int a = 0; a < numberOfAntenna; a++) {

		// for each antenna go through each transceiver (User Equipment)
		// and perform the following instructions
		for (int t = 0; t < numberOfTranceivers; t++) {

			Packet outgoingPacket(t, objID);	// Create an object of type packet using the transceiver number and object ID
			outgoingBuffer.push_back(outgoingPacket); // add the packet to the outgoing buffer

		}

		// call createSignalFromData(outgoingbuffer) iteratively for each antenna
		MIMOs[a].createSignalFromData(outgoingBuffer);

		// go through each signal in outgoing and use the sender in the packet so you know
		// which transceiver has the pointer to the correct device.
		// use the pointer to add the signal to the cellular device incomingsignals buffer
		for (int i = 0; i < outgoingBuffer.size(); i++) {

			Packet temp = outgoingBuffer[i]; // iterates through the outgoing buffer and stores the packet temporarily
			
			// TODO: use the send piece of the packet to determine which transceiver has the pointer to the correct device
			//       and add the signal to the UserEquipment incomingsignals buffer

		}

	}

	return false;
}
