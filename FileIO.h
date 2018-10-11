#pragma once
#include "GlobalVar.h"
#include <iostream> 
#include <fstream>
#include <sstream>

namespace FileIO
{
	using namespace std;

	//Writes file from program state.
	bool writeSaveFileFromENV(string filePath)
	{

		//Prints the filepath, just for diagnostic purposes
		cout << "\nFilename: " << filePath << endl;

		//Creates ofstream object, trunc means that previous file content is discarded.
		ofstream file_obj(filePath, ios::trunc | ios::binary);

		//Checks to make sure the object was created successfully.
		if (!file_obj)
			return false;

		//Outputs plain integer global variables to file. 
		file_obj.write((char *)& row, sizeof(int));
		file_obj.write((char *)& col, sizeof(int));
		file_obj.write((char *)& numberOfBaseStations, sizeof(int));
		file_obj.write((char *)& numberOfUsers, sizeof(int));
		file_obj.write((char *)& objectCount, sizeof(int));
		file_obj.write((char *)& envClock, sizeof(int));
		file_obj.write((char *)& shapeSideLength, sizeof(int));
		file_obj.write((char *)& numberOfAntenna, sizeof(int));
		file_obj.write((char *)& numberOfTranceivers, sizeof(int));

		//Outputs values from each env[][] location to file.
		for (int j = 0; j < row; j++)
		{
			for (int i = 0; i < col; i++)
			{
				int objID = env[j][i].getObjID();
				file_obj.write((char*)& objID, sizeof(int));
				int y = env[j][i].getY();
				file_obj.write((char*)& y, sizeof(int));
				int x = env[j][i].getX();
				file_obj.write((char*)& x, sizeof(int));
				int environmentFactor = env[j][i].getEnvironmentFactor();
				file_obj.write((char*)& environmentFactor, sizeof(int));
				int userAmt = env[j][i].getUserAmt();
				file_obj.write((char*)& userAmt, sizeof(int));
			}
		}

		//Outputs values from each BaseStation to file.
		for (int n = 0; n < numberOfBaseStations; n++)
		{
			int objID = BaseStationList[n].getObjID();
			file_obj.write((char *)& objID, sizeof(int));
			int y = BaseStationList[n].getY();
			file_obj.write((char *)& y, sizeof(int));
			int x = BaseStationList[n].getX();
			file_obj.write((char *)& x, sizeof(int));
			int traffic = BaseStationList[n].getMaxBandwith();
			file_obj.write((char *)& traffic, sizeof(int));

			{
				/*//Outputs size of region to file.
				int size = (int)(BaseStationList[n].getCurrentRegion().size());
				file_obj.write((char*)& size, sizeof(int));

				//Outputs values from each regionunit to file.
				for (size_t i = 0; i < BaseStationList[n].getCurrentRegion().size(); i++)
				{
					int y = BaseStationList[n].getCurrentRegion()[i].A->getY();
					file_obj.write((char*)& y, sizeof(int));
					int x = BaseStationList[n].getCurrentRegion()[i].A->getX();
					file_obj.write((char*)& x, sizeof(int));
					int antenna = BaseStationList[n].getCurrentRegion()[i].antenna;
					file_obj.write((char*)& antenna, sizeof(int));
					char symbol = BaseStationList[n].getCurrentRegion()[i].symbol;
					file_obj.write((char*)& symbol, sizeof(char));
				}*/
			}

			{
				/*//Outputs size of region to file.
				int size = (int)(BaseStationList[n].getDefaultRegion().size());
				file_obj.write((char*)& size, sizeof(int));

				//Outputs values from each regionunit to file.
				for (size_t i = 0; i < BaseStationList[n].getDefaultRegion().size(); i++)
				{
					int y = BaseStationList[n].getDefaultRegion()[i].A->getY();
					file_obj.write((char*)& y, sizeof(int));
					int x = BaseStationList[n].getDefaultRegion()[i].A->getX();
					file_obj.write((char*)& x, sizeof(int));
					int antenna = BaseStationList[n].getDefaultRegion()[i].antenna;
					file_obj.write((char*)& antenna, sizeof(int));
					char symbol = BaseStationList[n].getDefaultRegion()[i].symbol;
					file_obj.write((char*)& symbol, sizeof(char));

				}*/
			}

		}

		//Outputs values from each user(UserEquipment) to file.
		for (int c = 0; c < numberOfUsers; c++)
		{
			int objID = userList[c].getObjID();
			int y = userList[c].getY();
			int x = userList[c].getX();
			file_obj.write((char *)& objID, sizeof(int));
			file_obj.write((char *)& y, sizeof(int));
			file_obj.write((char *)& x, sizeof(int));
		}

		//Closes file object.
		file_obj.close();


		return true;
	}

	//Reads file into program state.
	bool readSaveFileToENV(string filePath)
	{
		//Prints the filepath, just for diagnostic purposes.
		cout << "\nFilename: " << filePath << endl;

		//Creates ifstream object, trunc means that previous file content is discarded.
		ifstream file_obj(filePath, ios::in | ios::binary);

		//Checks to make sure the object was created successfully.
		if (!file_obj)
			return false;

		//Reads plain integer global variables from file.
		file_obj.read((char *)& row, sizeof(int));
		file_obj.read((char *)& col, sizeof(int));
		file_obj.read((char *)& numberOfBaseStations, sizeof(int));
		file_obj.read((char *)& numberOfUsers, sizeof(int));
		file_obj.read((char *)& objectCount, sizeof(int));
		file_obj.read((char *)& envClock, sizeof(int));
		file_obj.read((char *)& shapeSideLength, sizeof(int));
		file_obj.read((char *)& numberOfAntenna, sizeof(int));
		file_obj.read((char *)& numberOfTranceivers, sizeof(int));

		//Allocates array for env from row/col values already read from file.
		env = new AreaUnit*[row];										
		for (int j = 0; j < row; j++)
			env[j] = new AreaUnit[col];


		//reads values to each env[][] location from file.
		for (int j = 0; j < row; j++)
		{
			for (int i = 0; i < col; i++)
			{
				int objID;
				file_obj.read((char*)& objID, sizeof(int));
				env[j][i].setObjID(objID);
				int y;
				file_obj.read((char*)& y, sizeof(int));
				int x;
				file_obj.read((char*)& x, sizeof(int));
				env[j][i].setYX(y, x);
				int environmentFactor;
				file_obj.read((char*)& environmentFactor, sizeof(int));
				env[j][i].setEnvironmentFactor(environmentFactor);
				int userAmt;
				file_obj.read((char*)& userAmt, sizeof(int));
				env[j][i].setUserAmt(userAmt);
			}
		}

		//Allocates array for BaseStationList from numberOfBaseStations value already read from file.
		BaseStationList = new BaseStation[numberOfBaseStations];

		//reads values for each BaseStation from file.
		for (int n = 0; n < numberOfBaseStations; n++)
		{
			{
				int objID;
				file_obj.read((char *)& objID, sizeof(int));
				BaseStationList[n].setObjID(objID);
				int y;
				file_obj.read((char *)& y, sizeof(int));
				int x;
				file_obj.read((char *)& x, sizeof(int));
				BaseStationList[n].setYX(y, x);
				int traffic;
				file_obj.read((char *)& traffic, sizeof(int));
				BaseStationList[n].setMaxBandwith(traffic);
			}


			{/*

				int size, x, y, antenna;
				char symbol;

				//Reads size of region from file.
				file_obj.read((char *)& size, sizeof(int));

				//Reads values to each regionunit from file.
				for (int i = 0; i < size; i++)
				{
					file_obj.read((char *)& y, sizeof(int));
					file_obj.read((char *)& x, sizeof(int));
					file_obj.read((char *)& antenna, sizeof(int));
					file_obj.read((char *)& symbol, sizeof(char));

					BaseStationList[n].addToCurrentRegion(env[y][x].getPointer(), symbol, antenna);
				}*/
			}

			{

				int size, x, y, antenna;
				char symbol;

				//Reads size of region from file.
				file_obj.read((char *)& size, sizeof(int));

				//Reads values to each regionunit from file.
				for (int i = 0; i < size; i++)
				{
					file_obj.read((char *)& y, sizeof(int));
					file_obj.read((char *)& x, sizeof(int));
					file_obj.read((char *)& antenna, sizeof(int));
					file_obj.read((char *)& symbol, sizeof(char));

					//BaseStationList[n].addToDefaultRegion(env[y][x].getPointer(), symbol, antenna);
				}
			}
		}

		//Allocates array for userList from numberOfusers value already read from file
		userList = new UserEquipment[numberOfUsers];

		{	
			//Reads values to each user(UserEquipment) from file.
			for (int c = 0; c < numberOfUsers; c++)
			{
				int objID;
				int y;
				int x;
				int volume;
				file_obj.read((char *)& objID, sizeof(int));
				file_obj.read((char *)& y, sizeof(int));
				file_obj.read((char *)& x, sizeof(int));
				file_obj.read((char *)& volume, sizeof(int));
				userList[c].setObjID(objID);
				userList[c].setYX(y, x);
				env[userList[c].getY()][userList[c].getX()].addUserEquipment(userList[c].getPointer());

			}
		}

		//Renders Env.
		//UserIO::renderEnvSymWithUsers();
		return true;
	}


///////////////////////////////////////////////////////////////////////////////////CURRENTLY_DEPRECATED/////////////////////////////////////////////////////////////////////////////////////////

	bool appendLog()
	{
		return true;
	}

	/*	bool writeSaveFileFromENV(int n)
	{
	stringstream filenum;														//creates string for filename
	filenum << n;																//
	string filename = (string)"Save" + filenum.str() + (string)".env";			//


	cout << "\nFilename: " << filename << endl;									//prints the filename, mainly for diagnostic purposes

	ofstream file_obj(filename, ios::trunc | ios::binary);									//creates ofstream object

	if (!file_obj)
	return false;

	file_obj.write((char *)& row, sizeof(int));
	file_obj.write((char *)& col, sizeof(int));
	file_obj.write((char *)& numberOfBaseStations, sizeof(int));
	file_obj.write((char *)& numberOfUsers, sizeof(int));
	file_obj.write((char *)& objectCount, sizeof(int));



	for (int j = 0; j < row; j++)												//
	{
	for (int i = 0; i < col; i++)											//
	{
	int objID = env[j][i].getObjID();
	file_obj.write((char*)& objID, sizeof(int));
	int y = env[j][i].getY();
	file_obj.write((char*)& y, sizeof(int));
	int x = env[j][i].getX();
	file_obj.write((char*)& x, sizeof(int));
	int environmentFactor = env[j][i].getEnvironmentFactor();
	file_obj.write((char*)& environmentFactor, sizeof(int));
	int userAmt = env[j][i].getUserAmt();
	file_obj.write((char*)& userAmt, sizeof(int));
	}
	}


	for (int n = 0; n < numberOfBaseStations; n++)										//
	{
	int objID = BaseStationList[n].getObjID();
	file_obj.write((char *)& objID, sizeof(int));
	int y = BaseStationList[n].getY();
	file_obj.write((char *)& y, sizeof(int));
	int x = BaseStationList[n].getX();
	file_obj.write((char *)& x, sizeof(int));
	int range = BaseStationList[n].getRange();
	file_obj.write((char *)& range, sizeof(int));
	int traffic = BaseStationList[n].getTraffic();
	file_obj.write((char *)& traffic, sizeof(int));
	bool alarm = BaseStationList[n].getAlarm();
	file_obj.write((char *)& alarm, sizeof(bool));
	int alarmID = BaseStationList[n].getAlarmID();
	file_obj.write((char *)& alarmID, sizeof(int));
	int EXP_Traffic = BaseStationList[n].getEXP_Traffic();
	file_obj.write((char *)& EXP_Traffic, sizeof(int));

	{
	int size = (int)(BaseStationList[n].getCurrentRegion().size());
	file_obj.write((char*)& size, sizeof(int));

	for (size_t i = 0; i < BaseStationList[n].getCurrentRegion().size(); i++)
	{
	int y = BaseStationList[n].getCurrentRegion()[i].A->getY();
	file_obj.write((char*)& y, sizeof(int));
	int x = BaseStationList[n].getCurrentRegion()[i].A->getX();
	file_obj.write((char*)& x, sizeof(int));
	int antenna = BaseStationList[n].getCurrentRegion()[i].antenna;
	file_obj.write((char*)& antenna, sizeof(int));
	char symbol = BaseStationList[n].getCurrentRegion()[i].symbol;
	file_obj.write((char*)& symbol, sizeof(char));
	}
	}

	{
	int size = (int)(BaseStationList[n].getDefaultRegion().size());
	file_obj.write((char*)& size, sizeof(int));

	for (size_t i = 0; i < BaseStationList[n].getDefaultRegion().size(); i++)
	{
	int y = BaseStationList[n].getDefaultRegion()[i].A->getY();
	file_obj.write((char*)& y, sizeof(int));
	int x = BaseStationList[n].getDefaultRegion()[i].A->getX();
	file_obj.write((char*)& x, sizeof(int));
	int antenna = BaseStationList[n].getDefaultRegion()[i].antenna;
	file_obj.write((char*)& antenna, sizeof(int));
	char symbol = BaseStationList[n].getDefaultRegion()[i].symbol;
	file_obj.write((char*)& symbol, sizeof(char));

	}
	}

	}

	for (int c = 0; c < numberOfUsers; c++)
	{

	int objID = userList[c].getObjID();
	int y = userList[c].getY();
	int x = userList[c].getX();
	int volume = userList[c].getVolume();
	file_obj.write((char *)& objID, sizeof(int));
	file_obj.write((char *)& y, sizeof(int));
	file_obj.write((char *)& x, sizeof(int));
	file_obj.write((char *)& volume, sizeof(int));
	}
	file_obj.close();


	return true;
	}*/

	/*	bool readSaveFileToENV(int n)
	{
	bool fileSuccess = true;													//the bool fileSuccess is true until set to false by an error

	//	envFile file;																//declares the file container to store variables to be read from file

	stringstream filenum;														//creates string for filename
	filenum << n;																//
	string filename = (string)"Save" + filenum.str() + (string)".env";			//


	cout << "\nFilename: " << filename << endl;									//prints the filename, mainly for diagnostic purposes

	ifstream file_obj(filename, ios::in | ios::binary);							//creates ofstream object

	if (!file_obj)
	return false;														//creates ofstream object

	file_obj.read((char *)& row, sizeof(int));
	file_obj.read((char *)& col, sizeof(int));
	file_obj.read((char *)& numberOfBaseStations, sizeof(int));
	file_obj.read((char *)& numberOfUsers, sizeof(int));
	file_obj.read((char *)& objectCount, sizeof(int));


	env = new AreaUnit*[row];												//allocates array for env within file
	for (int j = 0; j < row; j++)											//
	env[j] = new AreaUnit[col];											//


	for (int j = 0; j < row; j++)											//
	{
	for (int i = 0; i < col; i++)										//
	{

	int objID;
	file_obj.read((char*)& objID, sizeof(int));
	env[j][i].setObjID(objID);
	int y;
	file_obj.read((char*)& y, sizeof(int));
	int x;
	file_obj.read((char*)& x, sizeof(int));
	env[j][i].setYX(y,x);
	int environmentFactor;
	file_obj.read((char*)& environmentFactor, sizeof(int));
	env[j][i].setEnvironmentFactor(environmentFactor);
	int userAmt;
	file_obj.read((char*)& userAmt, sizeof(int));
	env[j][i].setUserAmt(userAmt);
	}
	}

	BaseStationList = new BaseStation[numberOfBaseStations];

	for (int n = 0; n < numberOfBaseStations; n++)
	{
	{
	int objID;
	file_obj.read((char *)& objID, sizeof(int));
	BaseStationList[n].setObjID(objID);
	int y;
	file_obj.read((char *)& y, sizeof(int));
	int x;
	file_obj.read((char *)& x, sizeof(int));
	BaseStationList[n].setYX(y, x);
	int range;
	file_obj.read((char *)& range, sizeof(int));
	BaseStationList[n].setRange(range);
	int traffic;
	file_obj.read((char *)& traffic, sizeof(int));
	BaseStationList[n].setTraffic(traffic);
	bool alarm;
	file_obj.read((char *)& alarm, sizeof(bool));
	BaseStationList[n].setAlarm(alarm);
	int alarmID;
	file_obj.read((char *)& alarmID, sizeof(int));
	BaseStationList[n].setAlarmID(alarmID);
	int EXP_Traffic;
	file_obj.read((char *)& EXP_Traffic, sizeof(int));
	BaseStationList[n].setEXP_traffic(EXP_Traffic);
	}


	{

	int size, x, y, antenna;
	char symbol;
	file_obj.read((char *)& size, sizeof(int));

	for (int i = 0; i < size; i++)
	{
	file_obj.read((char *)& y, sizeof(int));
	file_obj.read((char *)& x, sizeof(int));
	file_obj.read((char *)& antenna, sizeof(int));
	file_obj.read((char *)& symbol, sizeof(char));

	BaseStationList[n].addToCurrentRegion(env[y][x].getPointer(), symbol, antenna);
	}
	}

	{

	int size, x, y, antenna;
	char symbol;
	file_obj.read((char *)& size, sizeof(int));

	for (int i = 0; i < size; i++)
	{
	file_obj.read((char *)& y, sizeof(int));
	file_obj.read((char *)& x, sizeof(int));
	file_obj.read((char *)& antenna, sizeof(int));
	file_obj.read((char *)& symbol, sizeof(char));

	BaseStationList[n].addToDefaultRegion(env[y][x].getPointer(), symbol, antenna);
	}
	}
	}



	userList = new UserEquipment[numberOfUsers];

	{
	for (int c = 0; c < numberOfUsers; c++)
	{
	int objID;
	int y;
	int x;
	int volume;
	file_obj.read((char *)& objID, sizeof(int));
	file_obj.read((char *)& y, sizeof(int));
	file_obj.read((char *)& x, sizeof(int));
	file_obj.read((char *)& volume, sizeof(int));
	userList[c].setObjID(objID);
	userList[c].setYX(y, x);
	userList[c].setVolume(volume);
	env[userList[c].getY()][userList[c].getX()].addUserEquipment(userList[c].getPointer());

	}
	}

	UserIO::renderEnvSymWithUsers();
	return true;
	}*/
	
}
