#pragma once
#include "AreaUnit.h"

//blank constructor (default)
AreaUnit::AreaUnit()
{
	;
}

//initializes blank areaunit as a grid placeholder
AreaUnit::AreaUnit(int i, int Y, int X, bool R)
{
	this->objID = i;
	this->y = Y;
	this->x = X;
	this->environmentFactor = 0;
	this->userAmt = 0;
	this->isCovered = R;
	this->symbol = ' ';
}

//initializes areaUnit within a region
AreaUnit::AreaUnit(int i, int Y, int X, bool R, char c)
{
	this->objID = i;
	this->y = Y;
	this->x = X;
	this->environmentFactor = 0;
	this->userAmt = 0;
	this->isCovered = R;
	this->symbol = c;
}


void AreaUnit::InitializeDefaults(int i, int Y, int X, bool R)
{
	this->objID = i;
	this->y = Y;
	this->x = X;
	this->environmentFactor = 0;
	this->userAmt = 0;
	this->isCovered = R;
	this->symbol = ' ';
}

void AreaUnit::InitializeDefaults(int i, int Y, int X, bool R, char c)
{
	this->objID = i;
	this->y = Y;
	this->x = X;
	this->environmentFactor = 0;
	this->userAmt = 0;
	this->isCovered = R;
	this->symbol = c;
}

//sets object ID
void AreaUnit::setObjID(int i)
{
	this->objID = i;
}
//sets XY coordinates
void AreaUnit::setYX(int Y, int X)
{
	this->y = Y;
	this->x = X;
}
//sets env factor
void AreaUnit::setEnvironmentFactor(int n)
{
	this->environmentFactor = n;
}

void AreaUnit::setSymbol(char sym)
{
	this->symbol = sym;
}

//sets amount of users in areaunit
void AreaUnit::setUserAmt(int n)
{
	this->userAmt = n;
}

//gets OBJID
int AreaUnit::getObjID()
{
	return this->objID;
}
//gets X
int AreaUnit::getX()
{
	return this->x;
}
//gets Y
int AreaUnit::getY()
{
	return this->y;
}
//gets env factor
int AreaUnit::getEnvironmentFactor()
{
	return 0;
}

char AreaUnit::getSymbol()
{
	return this->symbol;
}

//gets user amt
int AreaUnit::getUserAmt()
{
	return this->userAmt;
}
void AreaUnit::setisCovered(bool rs)
{
	this->isCovered = rs;
}
bool AreaUnit::getisCovered()
{
	return this->isCovered;
}
//returns a pointer to current areaunit
AreaUnit* AreaUnit::getPointer()
{
	return this;
}

void AreaUnit::addUserEquipment(UserEquipment* d, int i)
{
	this->users.push_back(d);
	this->getUserEquipment(i)->initializeUserEquipment(this->y, this->x, objectCount);
}

void AreaUnit::addUserEquipment(UserEquipment* d)
{
	this->users.push_back(d);
}

UserEquipment* AreaUnit::getUserEquipment(int i)
{
	return this->users[(size_t)i];
}

DeviceList AreaUnit::getUsers()
{
	return this->users;
}

//not in current use, to be built later
void AreaUnit::update()
{
	;				//updates variables based off of typical conditions and chance fluctuations
}

