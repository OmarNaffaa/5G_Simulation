//This file contains global containers and files for important program environment state information.
//BE CAREFUL MODIFYING ANYTHING HERE.

//Declares classes because there are pointers to class instances within this file
class BaseStation;
class AreaUnit;
class UserEquipment;

//Number of rows in env
extern int row;
//Number of cols in env
extern int col;
//Number of number of BaseStations in env
extern int numberOfBaseStations;
//Number of number of users
extern int numberOfUsers;
//Number of number of objects
extern int objectCount;

extern int envClock;

extern int shapeSideLength;

extern int numberOfAntenna;

extern int numberOfTranceivers;

extern double distanceBetweenTranceivers;


//A 2 dim array which consists of AreaUnits and is the foundation of the environment
extern AreaUnit** env;
//A 1 dim array which consists of BaseStation objects
extern BaseStation* BaseStationList;
//A 1 dim array which consists of UserEquipment objects
extern UserEquipment* UserEquipmentList;


