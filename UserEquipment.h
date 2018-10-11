#pragma once
#include "DataPackets.h"
#include "Signal.h"
#include <vector>

class BaseStation;

class UserEquipment
{
protected:
	int objID;
	int userID;
	int y, x;

	Signals dataReceived;

public:
	int getObjID();
	int getUserID();
	int getX();
	int getY();
	void initializeUserEquipment(int,int,int);
	Signals getData();
	void receiveData(Signals, bool);
	void setYX(int,int);
	UserEquipment* getPointer();
	void setObjID(int);
	void setUserID(int);
};

typedef std::vector<UserEquipment*> DeviceList;
