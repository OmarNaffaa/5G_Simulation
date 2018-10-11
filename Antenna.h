#pragma once
#include <vector>
#include "Signal.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Tranceivers.h"

class AreaUnit;
class BaseStation;



class Antenna
{
protected:
	const static double distanceBetweenTranceivers;
	int y, x;
	double exactY, exactX;
	Signals outgoing;
	TranceiverList manifest;
	PacketBundle outgoingBuffer;
public:

	Antenna();

	void initialize(int Y, int X);

	void setExactYX(double Y, double X);

	int getY();

	int getX();

	double getExactY();

	double getExactX();

	void createSignalFromData(PacketBundle data);

	void addTranceiver(UserEquipment*);

	TranceiverList getManifest();

	//void sendSignalAcrossRegion(bool b = false);

	

};