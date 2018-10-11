#pragma once
#include "GlobalVar.h"
#include <iostream>
#include "BaseStation.h"
#include "AreaUnit.h"
#include <vector>
#include <string>
#include "NewEnvironmentInitialization.h"
#include "Tranceivers.h"

namespace UserIO
{

	//Returns number of digits of a number.
	int numberOfDigits(int num)
	{
		int digits = 0;

		//Makes num positive
		if (num < 0)
			num *= -1;

		//reduces integer num to 0 by successive divisions by 10 while...
		//counting the digits
		while (num != 0)
		{
			num /= 10;
			digits++;
		}
		return digits;
	}
	
	//Outputs all information about BaseStation to screen
	void printBaseStation(BaseStation* N)
	{
		std::cout << std::endl;
		std::cout << "BaseStation:" << std::endl;
		std::cout << "\tObjID: " << N->getObjID() << std::endl;
		std::cout << "\tY,X: " << N->getY() << "," << N->getX() << std::endl;
		std::cout << "\tBandwith: " << N->getMaxBandwith() << std::endl;

		std::cout << "\tAntennas:" << std::endl;
		for (int i = 0; i < numberOfAntenna; i++)
		{
			std::cout << "\t\t(" << N->getAntennaList()[i].getExactY() << ',' << N->getAntennaList()[i].getExactX() << ") : ";
			for (size_t j = 0; j < N->getAntennaList()[i].getManifest().Tranceivers.size(); j++)
				std::cout << N->getAntennaList()[i].getManifest()[j].user->getObjID() << "  ";
		}

		/*//Displays information about region entries
		std::cout << std::endl << "Region(Current):" << std::endl;
		for (size_t i = 0; i < N->getCurrentRegion().size(); i++)
		{
			std::cout << "\tArea " << i << ": ";
			std::cout << '(' << N->getCurrentRegion()[i].A->getY() << ',' << N->getCurrentRegion()[i].A->getX() << ")  ObjID: " << N->getCurrentRegion()[i].A->getObjID();
			if (i % 5 == 0)
				std::cout << std::endl;l
		}

		//Displays information about region entries
		std::cout << std::endl << "Region(Default):" << std::endl;
		for (size_t i = 0; i < N->getDefaultRegion().size(); i++)
		{
			std::cout << "\tArea " << i << ": ";
			std::cout << '(' << N->getDefaultRegion()[i].A->getY() << ',' << N->getDefaultRegion()[i].A->getX() << ")  ObjID: " << N->getDefaultRegion()[i].A->getObjID();
			if (i % 5 == 0)
				std::cout << std::endl;
		}*/
	}
	
	//Outputs all information about AreaUnit to screen
	void printAreaUnit(AreaUnit* A)
	{
		std::cout << std::endl;
		std::cout << "AreaUnit:" << std::endl;
		std::cout << "\tObjID: " << A->getObjID() << std::endl;
		std::cout << "\tY,X: " << A->getY() << "," << A->getX() << std::endl;
		std::cout << "\tEnvironment Factor: " << A->getEnvironmentFactor() << std::endl;
		std::cout << "\tEXP Environment Factor: " << A->getEnvironmentFactor() << std::endl;
		std::cout << "\tUserAmt: " << A->getUserAmt() << std::endl;

		//Displays information about user entries
		std::cout << "Users:";
		for (int i = 0; i < A->getUserAmt(); i++)
		{
			std::cout << "\tUser " << i << ": ";
			std::cout << '(' << A->getUserEquipment(i)->getY() << ',' << A->getUserEquipment(i)->getX() << ")  ObjID: " << A->getUserEquipment(i)->getObjID() << std::endl;
		}
	}

	//Same as printBaseStation but without printing region entries.
	void printBaseStationWithoutRegion(BaseStation* N)
	{
		std::cout << std::endl;
		std::cout << "BaseStation:" << std::endl;
		std::cout << "\tObjID: " << N->getObjID() << std::endl;
		std::cout << "\tY,X: " << N->getY() << "," << N->getX() << std::endl;
		std::cout << "\tTraffic: " << N->getMaxBandwith() << std::endl;

		std::cout << "\tAntennas:" << std::endl;
		for (int i = 0; i < numberOfAntenna; i++)
		{
			std::cout << "\t\t(" << N->getAntennaList()[i].getY() << ',' << N->getAntennaList()[i].getX() << ") : ";
			for (size_t j = 0; j < N->getAntennaList()[i].getManifest().Tranceivers.size(); j++)
				std::cout << N->getAntennaList()[i].getManifest()[j].user->getObjID() << "  ";
		}

	}

	//Template function takes a vector of type T.
	//This type T is ALWAYS supposed to be a reference type.
	//This is because this function is supposed to take user...
	//input and put it into the members of the vector by reference.
	//The funcction also takes a string to output, functioning as...
	// a prompt for the user.
	template <typename T>
	bool userInput(std::vector<T>inputContainers, const char str[])
	{
		//The user gets a certain number of tries to input correct values., char* str
		int tries;

		//Outputs provided string argument.
		std::cout << str << std::endl;

		//Goes through each member of vector to input data into it.
		for (int i = 0; i < (int)inputContainers.size(); i++)
		{
			//For each member of input vector user gets 5 tries.
			tries = 5;

			//Loop repeats while there are tries remaining...
			//and std::cin.fail() returns true (indicating input failure).
			do
			{
				std::cin >> *inputContainers[i];	//gets user input
				std::cin.clear();					//clears input stream
				std::cin.ignore(INT_MAX, '\n');		//helps clear input stream
			} while (std::cin.fail() && (--tries)>0);
			
		}

		//If user successfully entered data tries is non-zero and thus returns true.
		return (bool)tries;
	}

	//Renders the environment with only the symbols
	void renderEnvSym()
	{
		//Clears the screen.
		//system("cls");

		//maximumDigitsCol represents the most digits a column number has in the env
		//E.g. if the env has 500 columns then maximumDigitsCol = 3;
		int maximumDigitsCol = numberOfDigits(col);

		//These loops are to denote the column value in printing the env.
		//outputs the highest digit first, counts down to lowest digit
		for (int digit = maximumDigitsCol - 1; digit >= 0; digit--)
		{
			//Cosmetic
			std::cout << "\t ";
			for (int i = 0; i < col; i++)
			{
				//converts the ith column to a string: colun 500: int: 500 -> string: "500"
				std::string num = std::to_string(i);

				//If the number is shorter than the current "digit" then a space is printed.
				if ((int)num.length() < digit)
					std::cout << ' ';
				//If the number length is equal to the current digit then the digit is printed.
				else
				{
					std::cout << num[digit];
				}
			}

			//Cosmetic
			std::cout << " " << std::endl;
		}

		//Decorative line
		std::cout << "\t ";
		for (int x = 0; x < col; x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;

		//Iterates through each coordinate printing the symbol there.
		for (int y = 0; y < row; y++)
		{
			std::cout << y << "\t|";
			for (int x = 0; x < col; x++)
			{
				std::cout << env[y][x].getSymbol();
			}
			std::cout << "|" << std::endl;

		}
		std::cout << "\t ";


		//Decorative line
		for (int x = 0; x < col; x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
		std::cout << "ENV Variables:\tRow#: " << row << "\tCol#: " << col << "\tNumber of BaseStations: " << numberOfBaseStations << "\tNumber of Users: " << numberOfUsers << "\tObject Count: " << objectCount << std::endl;


	}

	//Renders the environment with the symbols and user amount
	void renderEnvSymWithUsers()
	{
		//SEE "renderEnvSym()" COMMENTS. THERE'S ONLY ONE DIFFERENCE WHICH IS EXPLAINED IN THE COMMENT BELOW.

		//system("cls");

		int maximumDigitsCol = numberOfDigits(col);		


		for (int digit = maximumDigitsCol-1; digit >= 0; digit--)
		{

			std::cout << "\t ";
			for (int i = 0; i < col; i++)
			{
				std::string num = std::to_string(i);
				if ((int)num.length() < digit)
					std::cout << ' ';
				else
				{
					std::cout << num[digit];
				}
			}
			std::cout << " " << std::endl;
		}

		std::cout << "\t ";
		for (int x = 0; x < col; x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;

		for (int y = 0; y < row; y++)
		{
			std::cout << y << "\t|";
			for (int x = 0; x < col; x++)
			{
				//If there are users present, that number of users gets printed instead of the symbol there.
				if (env[y][x].getUserAmt() > 0)
					std::cout << env[y][x].getUserAmt();
				else
					std::cout << env[y][x].getSymbol();
			}
			std::cout << "|" << std::endl;

		}
		std::cout << "\t ";
		for (int x = 0; x < col; x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
		std::cout << "ENV Variables:\tRow#: " << row << "\tCol#: " << col << "\tNumber of BaseStations: " << numberOfBaseStations << "\tNumber of Users: " << numberOfUsers << "\tObject Count: " << objectCount << std::endl;
		
	}

	void renderBaseStationRegionsByAntenna()
	{

		//system("cls");


		int** tmpEnv = new int*[row];
		for (int i = 0; i < row; i++)
		{
			tmpEnv[i] = new int[col];
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				tmpEnv[i][j] = -1;
			}
		}

		for (int n = 0; n < numberOfBaseStations; n++)
		{
			for (int antenna = 0; antenna < numberOfAntenna; antenna++)
			{
				double antennaExactY = BaseStationList[n].getAntennaList()[antenna].getExactY();
				double antennaExactX = BaseStationList[n].getAntennaList()[antenna].getExactX();
				std::cout << "Antenna #" << antenna << " exY: " << antennaExactY << " exX: " << antennaExactX << std::endl;
			}
		}


		for (int n = 0; n < numberOfBaseStations; n++)
		{
			for (int regionUnit = 0; regionUnit < BaseStationList[n].getRegionSize(); regionUnit++)
			{
				double minDistance = -1;
				int minAntenna;

				int currUnitY = BaseStationList[n][regionUnit].y;
				int currUnitX = BaseStationList[n][regionUnit].x;

				for (int antenna = 0; antenna < numberOfAntenna; antenna++)
				{

					double antennaExactY = BaseStationList[n].getAntennaList()[antenna].getExactY();
					double antennaExactX = BaseStationList[n].getAntennaList()[antenna].getExactX();
					//std::cout << "Antenna #" << antenna << " exY: " << antennaExactY << " exX: " << antennaExactX << std::endl;
					double distance = (currUnitX - antennaExactX)*(currUnitX - antennaExactX) + (currUnitY - antennaExactY)*(currUnitY - antennaExactY);
					if (minDistance < 0)
					{
						minDistance = distance;
						minAntenna = antenna;
					}
					else if (distance < minDistance)
					{
						minDistance = distance;
						minAntenna = antenna;
					}
				}
				tmpEnv[currUnitY][currUnitX] = minAntenna + 1;

			}
		}

		int maximumDigitsCol = numberOfDigits(col);


		for (int digit = maximumDigitsCol - 1; digit >= 0; digit--)
		{

			std::cout << "\t ";
			for (int i = 0; i < col; i++)
			{
				std::string num = std::to_string(i);
				if ((int)num.length() < digit)
					std::cout << ' ';
				else
				{
					std::cout << num[digit];
				}
			}
			std::cout << " " << std::endl;
		}

		std::cout << "\t ";
		for (int x = 0; x < col; x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;

		for (int y = 0; y < row; y++)
		{
			std::cout << y << "\t|";
			for (int x = 0; x < col; x++)
			{
				if (tmpEnv[y][x] > 0)
					std::cout << tmpEnv[y][x];
				else
					std::cout << ' ';
			}
			std::cout << "|" << std::endl;

		}
		std::cout << "\t ";
		for (int x = 0; x < col; x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
		std::cout << "ENV Variables:\tRow#: " << row << "\tCol#: " << col << "\tNumber of BaseStations: " << numberOfBaseStations << "\tNumber of Users: " << numberOfUsers << "\tObject Count: " << objectCount << std::endl;

	}

	//Same as printAreaUnit but without printing user entries.
	/*void printAreaUnitWithoutCellDevices(AreaUnit* A)
	{
		std::cout << std::endl;
		std::cout << "AreaUnit:" << std::endl;
		std::cout << "\tObjID: " << A->getObjID() << std::endl;
		std::cout << "\tY,X: " << A->getY() << "," << A->getX() << std::endl;
		std::cout << "\tEnvironment Factor: " << A->getEnvironmentFactor() << std::endl;
		std::cout << "\tEXP Environment Factor: " << A->getEnvironmentFactor() << std::endl;
		std::cout << "\tUserAmt: " << A->getUserAmt() << std::endl;

	}*/
}