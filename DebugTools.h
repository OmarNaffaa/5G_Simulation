#pragma once
#include "GlobalVar.h"
#include <Windows.h>
#include "BaseStation.h"
#include "AreaUnit.h"
#include "UserIO.h"

//namespace declaration for debugging tools
namespace DBGTools
{
	//To avoid writing std:: infront of cout/endl
	using namespace std;

	//This function allows the user to examine the individual components of the environment...
	//purely for debugging purposes.
	bool environmentDiagnostic()
	{
		//Loop is only broken if users enter a -1 as a coordinate value.
		while (true)
		{
			//tmp_row & tmp_col are the containers for user selected y,x location.
			int tmp_row = 0, tmp_col = 0;

			//The vector is the container for UserIO::userInput() inputs.
			vector<int*>input = { &tmp_row, &tmp_col };

			//The do..while loop repeats while user has not entered a valid coordinate for env[][] or a -1
			//This helps to vet the input
			do
			{
				//Prompts the user for y,x coordinates.
				if (!UserIO::userInput(input, "\nEnter object y,x:  "))
				{
					cout << "Input failed, exiting" << endl;
					return false;
				}
				//cout << "Input invalid try again:" << endl;
			} while (!(tmp_row < row && tmp_col < col && tmp_row >= 0 && tmp_col >= 0) && !(tmp_row != -1 || tmp_col != -1));


			//Creates simplified copy of the real env[][] in the form of a 2-dim int array.
			int **BaseStationNumEnv = new int*[row];
			for (int j = 0; j < row; j++)
				BaseStationNumEnv[j] = new int[col];

			//Initializes each value in BaseStationNumEnv to -1.
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
					BaseStationNumEnv[i][j] = -1;

			//Declares two ints which will represent each BaseStation coordinate pair.
			int x, y;

			//Iterates through the BaseStationList thus each BaseStation
			for (int BaseStation = 0; BaseStation < numberOfBaseStations; BaseStation++)
			{		
					//sets x&y equal to the BaseStation's x,y
					x = BaseStationList[BaseStation].getX();
					y = BaseStationList[BaseStation].getY();

					//Sets the corresponding location of the int BaseStationNumEnv array equal to the objID of the BaseStation
					BaseStationNumEnv[y][x] = BaseStationList[BaseStation].getObjID();
					//This will allow for the next part to know if the coords the user inputted also has a BaseStation on it.
			}

			//If the user entered a -1 the function breaks
			if (tmp_row == -1 || tmp_col == -1)
				break;
			//If the int BaseStationNumEnv array isn't equal to -1 and is a valid BaseStation number...
			//the AreaUnit and BaseStation that correspond to the user entered coordinate will print.
			else if (BaseStationNumEnv[tmp_row][tmp_col] != -1)
			{
				//Prints the AreaUnit information of the env[][] location the user entered.
				UserIO::printAreaUnit(env[tmp_row][tmp_col].getPointer());
				//Prints the BaseStation information of the BaseStation located on the env[][] location the user entered.
				UserIO::printBaseStation(BaseStationList[BaseStationNumEnv[tmp_row][tmp_col]].getPointer());
			}
			//Just prints the AreaUnit information of the env[][] location the user entered, no BaseStation here.
			else
				//Prints the AreaUnit information of the env[][] location the user entered.
				UserIO::printAreaUnit(env[tmp_row][tmp_col].getPointer());
		}
		return true;
	}

///////////////////////////////////////////////////////////////////////////////////CURRENTLY_DEPRECATED/////////////////////////////////////////////////////////////////////////////////////////

/*	bool envTestingForFileTesting()
	{
		while (true)
		{
			cout << endl << "Enter object x,y" << endl;

			int tmp_row, tmp_col;
			int tries = 5;
			do
			{
				cin >> tmp_col >> tmp_row;
			} while (cin.fail() && --tries);
			cin.clear();
			cin.ignore(INT_MAX, '\n');


			if (tmp_row == -1 || tmp_col == -1)
				break;
			else 
				UserIO::printAreaUnitWithoutCellDevices(env[tmp_row][tmp_col].getPointer());
				
		}
		return true;
	}*/

/*	bool envPrintAll()
	{
		

		int **BaseStationNumEnv = new int*[row];
		for (int j = 0; j < row; j++)
			BaseStationNumEnv[j] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				BaseStationNumEnv[i][j] = -1;

		int x, y;
		for (int BaseStation = 0; BaseStation < numberOfBaseStations; BaseStation++)
		{
			for (size_t regUnit = 0; regUnit < BaseStationList[BaseStation].getCurrentRegion().size(); regUnit++)
			{
				x = BaseStationList[BaseStation].getX();
				y = BaseStationList[BaseStation].getY();
				BaseStationNumEnv[y][x] = BaseStationList[BaseStation].getObjID();
			}

		}

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				if (i == -1 || j == -1)
					break;
				else if (BaseStationNumEnv[i][j] != -1)
				{
					UserIO::printAreaUnit(env[i][j].getPointer());
					UserIO::printBaseStation(BaseStationList[BaseStationNumEnv[i][j]].getPointer());
				}
				else
					UserIO::printAreaUnit(env[i][j].getPointer());
			}
		
		return true;
	}*/
}