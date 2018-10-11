#include "UserEquipment.h"
#include "BaseStation.h"
#include <map>
#include "Signal.h"

//gets OBJID
int UserEquipment::getObjID()
{
	return this->objID;
}

//gets USERID
int UserEquipment::getUserID()
{
	return this->userID;
}

//gets X
int UserEquipment::getX()
{
	return this->x;
}

//gets Y
int UserEquipment::getY()
{
	return this->y;
}

// initializes a UserEquipment based on the location given (y, x) and the object ID
void UserEquipment::initializeUserEquipment(int Y, int X, int ID)
{
	this->y = Y;
	this->x = X;
	this->objID = ID;
}

// used to acknowledge whether or not the signal was received
Signals UserEquipment::getData()
{
	return this->dataReceived;
}

// ** ASK ABOUT THIS ONE **
/*void UserEquipment::receiveData(Signals p, bool updateBaseStation)
{
	this->dataReceived = p;

	if (updateBaseStation && p.size())
	{
		int randFrequencyFromPacketsReceived = rand() % p.size();
		this->Tranceiver = BaseStationList[p[0].getData()[0].sender].getPointer();
		this->Tranceiver->addTranceiver(std::make_pair(this->getObjID(), p[randFrequencyFromPacketsReceived].getFrequency()));\
	}
}*/

// sets the location of the UserEquipment in the format (y, x)
void UserEquipment::setYX(int Y, int X)
{
	this->y = Y;
	this->x = X;
}

// returns a pointer pointing to the current UserEquipment object
UserEquipment* UserEquipment::getPointer()
{
	return this;
}

// sets a UserEquipment object's object ID
void UserEquipment::setObjID(int n)
{
	this->objID = n;
}

// sets a UserEquipment object's user ID
void UserEquipment::setUserID(int n)
{
	this->userID = n;
}

