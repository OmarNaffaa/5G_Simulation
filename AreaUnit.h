#pragma once
#include "GlobalVar.h"
#include "vector"
#include <iostream> 
#include "UserEquipment.h"
#include "Signal.h"


typedef std::vector<UserEquipment*> DeviceList;

class AreaUnit
{
protected:
	int objID;
	int y, x;
	int environmentFactor;
	char symbol;
	int userAmt;
	bool isCovered;
	DeviceList users;



public:

	AreaUnit();

	AreaUnit(int, int, int, bool);

	AreaUnit(int, int, int, bool, char);

	void InitializeDefaults(int, int, int, bool);

	void InitializeDefaults(int, int, int, bool, char);

	void setObjID(int);

	void setYX(int, int);

	void setEnvironmentFactor(int);

	void setSymbol(char);

	void setUserAmt(int);

	void setisCovered(bool);

	int getObjID();

	int getX();

	int getY();

	int getEnvironmentFactor();

	char getSymbol();

	int getUserAmt();

	bool getisCovered();

	AreaUnit* getPointer();

	UserEquipment* getUserEquipment(int i);
	
	DeviceList getUsers();

	void addUserEquipment(UserEquipment*, int i);
	void addUserEquipment(UserEquipment*);


	void update();
};
