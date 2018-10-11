#pragma once
#include "GlobalVar.h"
#include <string>
#include <vector>
#include "UserIO.h"
#include "AreaUnit.h"
#include "BaseStation.h"
#include "UserEquipment.h"
#include <Windows.h>
#include "Antenna.h"
#include "Point.h"

#define SMALLEST_SIDE_LENGTH 0
#define LEAST_ANTENNAE 3

/////////////////////////////////////////////////DECLARING GLOBAL VARIABLES///////////////////////////////////////////////////////////////////////

AreaUnit** env;
BaseStation* BaseStationList;
UserEquipment* userList;
int row;
int col;
int numberOfBaseStations = 0;
int numberOfUsers = 0;
int objectCount = 0;
int envClock = 0;
int shapeSideLength;
int numberOfAntenna;
int numberOfTranceivers;
double distanceBetweenTranceivers;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace newENV
{

	using namespace std;

	//The type "Shape" is a 2d array of ShapeUnits which contain a bool value, and a char value.
	//A positive bool value indicates that the unit represents a shaded portion of the shape.
	//the char value contains the symbol which will be transmitted onto the regionUnits it gets mapped with.
	typedef struct
	{
		bool b;
		char sym;
	}ShapeUnit;
	typedef ShapeUnit** Shape;

	//The int value indicates the objID/number of the BaseStation which will take the EnvTUnit->AreaUnit into its regions.
	//the char value contains the symbol which will be transmitted onto the regionUnits it gets mapped with.
	typedef vector< vector<int> > envT;

	int shapeRow, shapeCol, side, middleRow, middleCol;

	//Returns a user-entered side length for hexagon generation and...
	//returns a bool error value by reference parameter to indicate if something went wrong.
	bool getSideLengthFromUser()
	{
		bool noError = true;
		//Gets side length from User
		//Note, the actual side length will not correspond to this, at least not the top and bottom sides...
		//This is really more of a scaling factor which gives you an idea of the hexagon size.
		vector<int*>input = { &side };
		if (!UserIO::userInput(input, "Enter hexagon side length\n"))
		{
			cout << "Input failed, exiting" << endl;
			noError = false;
			return 0;
		}

		//Side value must be odd.
		if (side % 2 == 0)
			side++;

		//Side value must be at least SMALLEST_SIDE_LENGTH
		//Also this weeds out negative numbers
		if (side < SMALLEST_SIDE_LENGTH)
			side = SMALLEST_SIDE_LENGTH;

		return noError;
	}

	//Returns the shape of the hexagon that will be used to generate the regions.
	Shape hexagonGenerator(bool& error)
	{
		//Declared the shape
		Shape hex;

		//The amount of rows (shapeRow) and amount of cols (shapeCol).
		//Determined by math.
		shapeRow = side * 2;
		shapeCol = 1 + 2 * side + 2 * (side - 1);

		//Creates shape in form of two dimensional array...
		//consisting of ShapeUnits.
		hex = new ShapeUnit*[shapeRow];
		for (int i = 0; i < shapeRow; i++)
			hex[i] = new ShapeUnit[shapeCol];

		//The middle column and middle row, to be used for BaseStation placement within the shape.
		//Determined by math.
		middleCol = 2 * side;
		middleRow = side;

		//Initialize all the shape's ShapeUnit's bool to false
		for (int y = 0; y < shapeRow; y++)
		{
			for (int x = 0; x < shapeCol; x++)
			{
				hex[y][x].b = false;
			}
		}

		//Iterates through the columns
		for (int i = 0; i <= shapeCol; i++)
		{
			//Pretty boring, but it initializes hex[][] bool values to true...
			//if the hex[][] location is within the desired hexagon.
			if (i < side)
			{
				for (int j = 0; j < i; j++)
				{
					hex[side - j - 1][i - 1].b = true;
					hex[side + j][i - 1].b = true;
				}
			}
			else if (i >= side  && i < 3*side + 1)
			{
				for (int j = 0; j < side; j++)
				{
					hex[side - j - 1][i - 1].b = true;
					hex[side + j][i - 1].b = true;
				}
			}
			else
			{
				for (int j = i - 3 * side; j < side; j++)
				{
					hex[j][i - 1].b = true;
					hex[2 * side - j - 1][i - 1].b = true;
				}
			}

		}
		/*
		//prints shape
		cout << endl;
		for (int y = 0; y < shapeRow; y++)
		{
			for (int x = 0; x < shapeCol; x++)
			{
				cout << hex[y][x].b;
			}
			cout << endl;
		}*/
		//Sleep(100000);
		return hex;
	}

	//Modifies the shape by reference to have accurate symbols.
	bool hexagonSymbolAdd(Shape& hex)
	{
		bool side1, side2, side3, side4, side6, side7, side8, side9;
		//Next two loops iterate through the rows and columns
		for (int i = 0; i < shapeRow; i++)
		{
			for (int j = 0; j < shapeCol; j++)
			{
				//The sides corresponds to the keys on a numberpad...
				//where 5 is the center and corresponds to the current location.
				//So if our coordinate is i,j = 1,1...side4 is 1,0; side9 is 0,2 etc...

				side1 = false;
				//These if statements for each side make sure the coordinate exists within hex[][]
				if (i + 1 < shapeRow && j - 1 >= 0)
					side1 = hex[i + 1][j - 1].b;

				side2 = false;
				if (i + 1 < shapeRow)
					side2 = hex[i + 1][j].b;

				side3 = false;
				if (i + 1 < shapeRow && j + 1 < shapeCol)
					side3 = hex[i + 1][j + 1].b;

				side9 = false;
				if (i - 1 >= 0 && j + 1 < shapeCol)
					side9 = hex[i - 1][j + 1].b;

				side4 = false;
				if (j - 1 >= 0)
					side4 = hex[i][j - 1].b;

				side6 = false;
				if (j + 1 < shapeCol)
					side6 = hex[i][j + 1].b;

				side7 = false;
				if (i - 1 >= 0 && j - 1 >= 0)
					side7 = hex[i - 1][j - 1].b;

				side8 = false;
				if (i - 1 >= 0)
					side8 = hex[i - 1][j].b;

				//The next series of if statements determine the appropriate symbol
				if (/*sides[0] &&*/ side2 && side3 /*&& sides[3]*/ && !side4 && side6 && !side7 && !side8)
				{
					hex[i][j].sym = '/';
				}
				else if (/*sides[0] &&*/ !side2 && !side3 /*&& sides[3]*/ && side4 && !side6 && side7 && side8)
				{
					hex[i][j].sym = '/';
				}
				else if (!side1 && !side2 /*&& sides[2]*/ && side9 && !side4 && side6 /*&& sides[6]*/ && side8)
				{
					hex[i][j].sym = '\\';
				}
				else if (side1 && side2 /*&& sides[2]*/ && !side9 && side4 && !side6 /*&& sides[6]*/ && !side8)
				{
					hex[i][j].sym = '\\';
				}
				else if (side1 && side2 && side3 && !side9 && side4 && side6 && !side7 && !side8)
				{
					hex[i][j].sym = (char)196;
				}
				else if (!side1 && !side2 && !side3 && side9 && side4 && side6 && side7 && side8)
				{
					hex[i][j].sym = (char)196;
				}
				else
				{
					hex[i][j].sym = ' ';
				}

			}
		}
		return true;
	}

	//Creates the first shape of the envTemplate.
	bool createFirstShape(Shape hex, envT &envTemplate, vector < Point > &BaseStationLocations)
	{
		//This is the middle point of the hex and therefore the BaseStation
		Point BaseStation = { middleRow - 1, middleCol - 1 };

		//Adds BaseStation to the BaseStation locations vector.
		BaseStationLocations.push_back(BaseStation);

		//for each row
		for (int i = 0; i < shapeRow; i++)
		{
			//Create an empty row.
			vector<int> row;

			//For each col.
			for (int j = 0; j < shapeCol; j++)
			{
				//If the shape and grid overlap the bool is intialized true which indicates that it's part of a region.
				if (hex[i][j].b)
				{
					row.push_back(numberOfBaseStations);
				}
				//Otherwise the areaunit is blank.
				else
				{
					row.push_back(-1);
				}

			}
			//Add the row to the main env vector.
			envTemplate.push_back(row);
		}

		numberOfBaseStations++;
		return true;

	}

	//When adding a shape, if the shape spills over the edge of the envTemplate...
	//we need to adjust the size of the envTemplate to accommodate the shape.
	bool adjustTemplateSize(Point &topLeft, Point &bottomRight, Point &currentBaseStation, envT &envTemplate, vector < Point > &BaseStationLocations)
	{
		//Documentation in first while loop below, should be easier to understand in context.
		//Short summary: after adjusting template some adjustment of the existing BaseStations has...
		//to occur, which is what this is for.
		Point increase = { 0,0 };

		//This while loop inserts a new ShapeUnit at the beginning of each row.
		//In essence adds new column.
		while (topLeft.x < 0)
		{
			for (size_t i = 0; i < envTemplate.size(); i++)
			{
				vector<int>::iterator it = envTemplate[i].begin();
				envTemplate[i].insert(it, -1);
			}
			//These things describe the key corner coordinates of the...
			//shape with regard to where youre trying to add it in the env template.
			//When new columns/rows are added to keep the coordinates from being negative...
			//the coordinates can be incremented accordingly.
			topLeft.x++;
			bottomRight.x++;
			currentBaseStation.x++;
			//Because this loop is supposed to keep topLeft.x from being less than 0...
			//we add a new column and this would through off the coordinates of the BaseStations we've already added.
			//The "increase" point increments to indicate how much the existing BaseStations should be adjusted. 
			increase.x++;
		}

		//This while loop inserts a new row to the envTemplate
		while (topLeft.y < 0)
		{
			//Creates the new row
			vector<int> row;
			for (size_t i = 0; i < envTemplate[0].size(); i++)
			{
				row.push_back(-1);
			}

			//Inserts the row.
			envT::iterator it = envTemplate.begin();
			envTemplate.insert(it, row);

			//See first loop.
			topLeft.y++;
			bottomRight.y++;
			currentBaseStation.y++;
			increase.y++;
		}

		//Adds new column to end.
		while (bottomRight.x > (int)envTemplate[0].size() - 1)
		{
			//for each row, adds blank ShapeUnit to end.
			for (size_t i = 0; i < envTemplate.size(); i++)
			{
				envTemplate[i].push_back(-1);
			}
		}

		//Adds new row to end.
		while (bottomRight.y > (int)envTemplate.size() - 1)
		{
			//Creates new row filled with blank ShapeUnits.
			vector<int> row;
			for (size_t i = 0; i < envTemplate[0].size(); i++)
			{
				row.push_back(-1);
			}
			//Adds row.
			envTemplate.push_back(row);

		}

		//Adjusts the BaseStation locations with regards to the increase tally.
		for (size_t i = 0; i < BaseStationLocations.size(); i++)
		{
			BaseStationLocations[i].y += increase.y;
			BaseStationLocations[i].x += increase.x;
		}

		return true;
	}

	//Adds a shape to the envtemplate.
	bool addShape(Shape hex, Point topLeft, Point currentBaseStation, Point shapeDim, envT &envTemplate, vector < Point > &BaseStationLocations)

	{
		//Makes sure that there isn't already a BaseStation where you're trying to put one.
		//bool checkForBaseStation = true;
		for (size_t i = 0; i < BaseStationLocations.size(); i++)
		{
			if (BaseStationLocations[i].y == currentBaseStation.y && BaseStationLocations[i].x == currentBaseStation.x)
				return false;
		}

		//Creates a point to store the BaseStation location and adds it to the BaseStationLocations vector.
		Point BaseStation = { currentBaseStation.y, currentBaseStation.x };
		BaseStationLocations.push_back(BaseStation);

		//For each row:
		for (int i = topLeft.y; i < topLeft.y + shapeDim.y; i++)
		{
			//For each col:
			for (int j = topLeft.x; j < topLeft.x + shapeDim.x; j++)
			{
				//If the shape and grid overlap the areaunit is intialized to a region or BaseStation...
				//also makes sure that the AU in question isn't already part of a region.
				if (hex[i - topLeft.y][j - topLeft.x].b && !(envTemplate[i][j] >= 0))
				{
					//Transfers the BaseStation number and symbol associated with the shape location.
					envTemplate[i][j] = numberOfBaseStations;
				}

			}

		}
		//Increments number of BaseStations.
		numberOfBaseStations++;
		return true;

	}

	//See similar functions in UserIO for documentation.
	void renderEnvBool(envT &envTemplate)
	{
		//SEE "renderEnvSym()" COMMENTS. THERE'S ONLY ONE DIFFERENCE WHICH IS EXPLAINED IN THE COMMENT BELOW.
		system("cls");

		int maximumDigitsCol = UserIO::numberOfDigits(envTemplate[0].size());


		for (int digit = maximumDigitsCol - 1; digit >= 0; digit--)
		{

			std::cout << "\t ";
			for (int i = 0; i < (int)envTemplate[0].size(); i++)
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
		for (int x = 0; x < (int)envTemplate[0].size(); x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;

		for (int y = 0; y < (int)envTemplate.size(); y++)
		{
			std::cout << y << "\t|";
			for (int x = 0; x < (int)envTemplate[0].size(); x++)
			{
				if (envTemplate[y][x] >= 0)
					//Indicates the region's BaseStation.
					std::cout << (envTemplate[y][x] + 1) % 10;
				else
					std::cout << ' ';
			}
			std::cout << "|" << std::endl;

		}
		std::cout << "\t ";

		for (int x = 0; x < (int)envTemplate[0].size(); x++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
	}

	//Allows user to create desired env template
	bool createTemplate(envT &envTemplate, vector< Point > &BaseStationLocations, Shape &s)
	{
		//Creates point containing shape dimensions.
		Point shapeDim = { shapeRow, shapeCol };

		//Creates point containing BaseStation location.
		Point currentBaseStation = { middleRow - 1, middleCol - 1 };

		bool loop = true;

		//Loop to add shape.
		//Loop exits when userInput is not 1<=x<=6.
		while (loop)
		{
			//Renders the ennTemplate.
			renderEnvBool(envTemplate);

			//Gets the side number from the user. 
			//The sideNum determines which side by which the new BaseStation will be connected by.
			string sideNum;
			std::vector<string*>input = { &sideNum };
			if (!UserIO::userInput(input, "Enter side number(1-6) that corresponds to side you want conjoined with next BaseStation\nSide 1 corresponds to the top side and the rest are clockwise sides in order\nEnter anything else to finish entering BaseStations\n"))
			{
				sideNum = -1;
				loop = false;
			}

			//This bool 
			bool BaseStationJumpLoop;

			//This loop only repeats if jumping between BaseStations.
			do
			{
				//Condition for loop repeat false by default, only true if BaseStation jumping.
				BaseStationJumpLoop = false;

				//Modifies the current BaseStation location in accordance with the side chosen.
				if (sideNum == "1")
				{
					currentBaseStation.y = currentBaseStation.y - 2 * side;
					currentBaseStation.x = currentBaseStation.x;
				}
				else if (sideNum == "2")
				{
					currentBaseStation.y = currentBaseStation.y - side;
					currentBaseStation.x = currentBaseStation.x + 3 * (side);
				}
				else if (sideNum == "3")
				{
					currentBaseStation.y = currentBaseStation.y + side;
					currentBaseStation.x = currentBaseStation.x + (3 * side);
				}
				else if (sideNum == "4")
				{
					currentBaseStation.y = currentBaseStation.y + 2 * side;
					currentBaseStation.x = currentBaseStation.x;
				}
				else if (sideNum == "5")
				{
					currentBaseStation.y = currentBaseStation.y + side;
					currentBaseStation.x = currentBaseStation.x - 3 * (side);
				}
				else if (sideNum == "6")
				{
					currentBaseStation.y = currentBaseStation.y - side;
					currentBaseStation.x = currentBaseStation.x - (3 * side);
				}
				else if (sideNum == "0")
				{
					//Allows the user to jump to another BaseStation.

					//num initialized to -1 for input vetting purposes.
					int num = -1;

					//Displays BaseStations already made.
					for (size_t i = 0; i < BaseStationLocations.size(); i++)
						std::cout << i + 1 << ": " << BaseStationLocations[i].y << "," << BaseStationLocations[i].x << std::endl;

					//Prompts user for BaseStation to jump to.
					std::vector<int*>intInput = { &num };
					if (UserIO::userInput(intInput, "Enter BaseStation to jump to: \n") && num < (int)BaseStationLocations.size() && num > 0)
					{
						//Sets current BaseStation to the BaseStation selected
						currentBaseStation.y = BaseStationLocations[num - 1].y;
						currentBaseStation.x = BaseStationLocations[num - 1].x;

						//Gets new side for the selected BaseStation.
						UserIO::userInput(input, "Enter side number(1 - 6) that corresponds to side you want conjoined with next BaseStation\nSide 1 corresponds to the top side and the rest are clockwise sides in order\n");

						//Causes loop to loop.
						BaseStationJumpLoop = true;
					}
				}
				else
					loop = false;

			} while (BaseStationJumpLoop);

			//These corners are created based off of the current BaseStation location and the known dimensions of the shape. 
			Point topLeftCorner = {
				currentBaseStation.y - side + 1,
				currentBaseStation.x - (side + side - 1)
			};

			Point bottomRightCorner = {
				topLeftCorner.y + shapeDim.y - 1,
				topLeftCorner.x + shapeDim.x - 1
			};

			//If the envtemplate has to be adjusted this will do its thing.
			adjustTemplateSize(topLeftCorner, bottomRightCorner, currentBaseStation, envTemplate, BaseStationLocations);

			//Adds shape.
			addShape(s, topLeftCorner, currentBaseStation, shapeDim, envTemplate, BaseStationLocations);
		}

		return true;
	}

	//Returns a user-entered side length for hexagon generation and...
	//returns a bool error value by reference parameter to indicate if something went wrong.
	bool getAntennaInfoFromUser()
	{
		bool noError = true;
		//Gets side length from User
		//Note, the actual side length will not correspond to this, at least not the top and bottom sides...
		//This is really more of a scaling factor which gives you an idea of the hexagon size.
		vector<int*>input1 = { &numberOfAntenna, &numberOfTranceivers };
		if (!UserIO::userInput(input1, "Enter number of antennae the BaseStations will have,\nthen enter the number of Tranceivers each antenna can have"))
		{
			cout << "Input failed, exiting" << endl;
			return noError = false;
		}

		
		std::string str = "Enter the distance between each tranceiver,\nit must be > 0 and < " + std::to_string(0.25 / numberOfTranceivers);
		vector<double*>input2 = { &distanceBetweenTranceivers };
		do
		{
			if (!UserIO::userInput(input2, str.c_str()))
			{
				cout << "Input failed, exiting" << endl;
				return noError = false;
			}
		} while (!(distanceBetweenTranceivers > 0) || !(distanceBetweenTranceivers < .25/numberOfTranceivers));

		//Side value must be odd.
		if (side < LEAST_ANTENNAE)
			side = LEAST_ANTENNAE;

		if (numberOfTranceivers <= 0)
			noError = false;

		return noError;
	}

	bool initializeTranceivers()
	{

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

				for (int d = 0; d < env[currUnitY][currUnitX].getUserAmt(); d++)
				{
					BaseStationList[n].getAntennaList()[minAntenna].addTranceiver(env[currUnitY][currUnitX].getUserEquipment(d)->getPointer());
				}

			}
		}
		return true;
	}

	//Get range of population, get odds of AU having people;
	//Applies random spread to all valid AU
	//Don't create special concentrations yet.
	bool userSpread()
	{
		//Get range of population, get odds of AU having people
		int userNum, oddsOfUser;
		vector<int*>input = { &userNum, &oddsOfUser };
		do
		{
			if (!UserIO::userInput(input, "\nEnter the maximum number of cellular users you want per area unit, \nthen enter the percentage of area units you want to have users\n"))
			{
				cout << "Input failed, exiting" << endl;
				return false;
			}
		} while (userNum < 0 || oddsOfUser < 0 || oddsOfUser > 100 || userNum > 9); //Checks to make sure the values are valid.

		//Declares variables that come into play next.
		int totalAmountOfUsers = 0, userAmt;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//If condition makes sure there isn't a BaseStation where you're trying to place users.
				if (env[i][j].getisCovered())
				{
					//If condition returns true oddsOfUser% of the time.
					if (rand() % 100 >= 100 - oddsOfUser)
					{
						//Generates a random user amount with the maximum being userNum.
						userAmt = (int)(rand() % (userNum + 1));


						//Sets the appropriate location to have userAmt.
						env[i][j].setUserAmt(userAmt);

						//Keeps track of total amount of users.
						totalAmountOfUsers += userAmt;
					}
				}
			}
		}

		//Keeps track of allocated users.
		int allocatedUsers = 0;

		//Allocates the userList container for all cellular devices created.
		userList = new UserEquipment[totalAmountOfUsers];

		//Iterates through env and creates the amount of cellular devices the areaunit specified.
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				for (int k = 0; k < env[i][j].getUserAmt(); k++)
				{
					//userList[allocatedUsers++].initializeUserEquipment(i, j, objectCount);
					env[i][j].addUserEquipment(userList[allocatedUsers++].getPointer(),k);
					objectCount++;
				}
			}
		}



		//Assigns the global user count to the allocated users.
		numberOfUsers = allocatedUsers;

		return true;
	}

	//Generates new environment.
	bool generateNewENV()
	{
		//Gets side from user.
		if (!newENV::getSideLengthFromUser())
			return false;
		else
			shapeSideLength = side;

		//Creates shape.
		bool noError = true;
		Shape s = newENV::hexagonGenerator(noError);
		if (!noError)
			return false;

		//Adds symbols to shape.
		if (!newENV::hexagonSymbolAdd(s))
			return false;
		
		
		//Declares the template for the new environment(envTemplate), and the list of BaseStation locations(BaseStation locations).
		envT envTemplate;
		vector< Point > BaseStationLocations;

		//Adds first shape to envTemplate.
		if (!createFirstShape(s, envTemplate, BaseStationLocations))
			return false;

		if (!createTemplate(envTemplate, BaseStationLocations, s))
			return false;

		
		//Initializes several global variables based off of the envTemplate dimensions.
		row = envTemplate.size();
		col = envTemplate[0].size();
		numberOfBaseStations = BaseStationLocations.size();

	//	if (!initializeFrequencyVariables())
	//		return false;

		//Initializes env.
		env = new AreaUnit*[row];
		for (int i = 0; i < row; i++)
			env[i] = new AreaUnit[col];

		if (!newENV::getAntennaInfoFromUser())
			return false;

		//Initializes BaseStationList.
		BaseStationList = new BaseStation[numberOfBaseStations];

		//Initializes actual BaseStations.
		for (int i = 0; i < numberOfBaseStations; i++)
		{
			int BaseStationY = BaseStationLocations[i].y;
			int BaseStationX = BaseStationLocations[i].x;
			BaseStationList[i].InitializeDefaults(BaseStationY, BaseStationX, objectCount++);
		}

		//Initializes the regions and the env they encompass
		for (int i = 0; i < numberOfBaseStations; i++)
		{
			int BaseStationY = BaseStationList[i].getY();
			int BaseStationX = BaseStationList[i].getX();

			int topLeftY = BaseStationY - side + 1;
			int topLeftX = BaseStationX - 2 * side + 1;

			//std::cout << "topleftY: " << topLeftY;
			//std::cout << "  topleftX: " << topLeftX << std::endl;
			//Sleep(10000);

			for (int k = topLeftY; k < 2 * side + topLeftY; k++)
			{
				for (int j = topLeftX; j < 4 * side + topLeftX - 1; j++)
				{
					if (s[k - topLeftY][j - topLeftX].b)
					{
						BaseStationList[i].addToRegion(k, j);
						//std::cout << "(" << k << "," << j << ")" << std::endl;
						if (k == BaseStationY && j == BaseStationX)
							env[k][j].InitializeDefaults(objectCount++, k, j, false);
						else
							env[k][j].InitializeDefaults(objectCount++, k, j, true);

						env[k][j].setSymbol(s[k - topLeftY][j - topLeftX].sym);
					}
				}
			}
			string num = to_string(i);
			env[BaseStationY][BaseStationX].setSymbol(num[num.size() - 1]);
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//If the location in env doesn't exist in a region
				if (envTemplate[i][j] == -1)
					env[i][j].InitializeDefaults(objectCount++, i, j, false);
			}
		}


		//Distribute users to env.
		userSpread();

		initializeTranceivers();

		//initializationUpdateEnv();
		
		//Renders the env.
		//UserIO::renderEnvSymWithUsers();
		return true;
	}

}