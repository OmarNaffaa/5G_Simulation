#pragma once
#include "GlobalVar.h"
#include <vector>
#include <map>
#include "DataPackets.h"
#include "Antenna.h"
#include "Point.h"


class BaseStation
{
protected:
	int objID;
	int y, x;
	int maxBandwith;

	Area region;
	Antenna* MIMOs;

	PacketBundle incomingBuffer;
	PacketBundle outgoingBuffer;
	
public:

	BaseStation();

	BaseStation(int, int, int);

	void InitializeDefaults(int i, int Y, int X);

	void addToRegion(int y, int x);
	Point& operator[] (int x);
	int getRegionSize();

	Antenna* getAntennaList();


	void setObjID(int);
	void setYX(int, int);
	void setMaxBandwith(int);
	int getObjID();
	int getY();
	int getX();
	int getMaxBandwith();

	PacketBundle getIncomingBuffer();
	PacketBundle getOutgoingBuffer();

	BaseStation* getPointer();

	void sendOutgoingBuffer(PacketBundle);


	bool Update();
};
