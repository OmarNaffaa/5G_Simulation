#include "GlobalVar.h"
#include "NewEnvironmentInitialization.h"
#include "DebugTools.h"
#include "FileIO.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <string>

//initializeEnvironment will offer user chance to open a file of choice or create a new file.
bool initializeEnvironment();

//openFromFile attempts to open a .env file from a user inputted name or location&name
bool openFromFile();

//saveToFile attempts to save a .env file to a user inputted name or location&name
bool saveToFile();

//This string gets initialized to the directory the executable lies in.
std::string programPath;


///////////////////////////////////////////////////////////////////////////////////BODY_OF_PROGRAM///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	//Seeds rand() function with the current time for its uses throughout program 
	srand((int)time(NULL));

	//Global string programPath set to the first string: argv[0]. 
	//This string is the directory the executable lies in.
	programPath = argv[0];

	//If the argument count (argc) is less than two it means the operating system...
	//did not pass the secondary argument that gets passed when the program was...
	//launched by opening a .env file.
	if (argc < 2)
	{
		//initializeEnvironment will offer user chance to open a file of choice or create a new file.
		if (!initializeEnvironment())	//if initializeEnvironment returns false it means something went horribly wrong and the program exits.
		{
			return 0;
		}
	}
	//The "else" case occurs when the argument count >=2, which will occur primarily...
	//when the program is launched by executing a .env save file.
	else
	{
		//The string filePath gets initialized to the second string in argv,
		//which contains the filepath of the .env file that the user clicked to open the program.
		std::string filePath(argv[1]);

		//Then, the filePath string gets passed to FileIO::readSaveFileToENV.
		//This function opens the file specified and attempts to parse it into the program state.
		//If it fails to do so it will return false causing the program to terminate. 
		if (!FileIO::readSaveFileToENV(filePath))
			return 0;
	}
	
	UserIO::renderBaseStationRegionsByAntenna();

	UserIO::renderEnvSym();

	UserIO::renderEnvSymWithUsers();

	//This function allows the user to examine the individual components of the environment...
	//purely for debugging purposes.
	DBGTools::environmentDiagnostic();



	//Quick message stating the program has finished.
	std::cout << "Finished";

	Sleep(1500 * 1000);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////BODY_FUNCTION_DEFINITIONS/////////////////////////////////////////////////////////////////////////////////////////

//initializeEnvironment will offer user chance to open a file of choice or create a new file.
bool initializeEnvironment()
{
	//Asks if user wants to read file or create a new environment.
	//Note the following 7 lines of code may look a bit complicated but all they do is...
	//output a string and safely attain user input. 
	//This UserIO::userInput() function and accompanying setup may seem a bit much but it's primarily for...
	//input vetting.
	char choice;
	std::vector<char*>input = { &choice };
	if (!UserIO::userInput(input, "Open file? (y/n)\n"))
	{
		std::cout << "Fatal input error, exiting\n" << std::endl;
		return false;
	}

	switch (choice)
	{
	case 'y':
	case 'Y':
	case '1':
		//The user has input 'y','Y, or '1'; so the program tries to initialize the environment from a file
		return openFromFile();
	case 'n':
	case 'N':
	case '2':
	{
		//The user has input 'n','N', or '2'; so the program tries to initialize a new environment
		if (!newENV::generateNewENV())
			return false;
		return true;
		//if the environment was created successfully the program will prompt the user to save it to a file
		//return saveToFile();
	}
	default:
		//extra input vetting. invalid inputs cause the function to return false.
		std::cout << "Invalid input: exiting now\n" << std::endl;		//vets user choice input
		return false;
	}
}

//openFromFile attempts to open a .env file from a user inputted name or location&name
bool openFromFile()
{
	//prompts user for filename/path+name
	std::cout << std::endl << "Enter filename/filepath+name:" << std::endl;

	//The string "name" is the container for the user input, it is deliberately...
	//set to an empty string in case the user decides to hit enter without entering anything...
	//thus vetting the input.
	std::string name = ""; 

	//Here I use getline instead of my typical user input function UserIO::userInput() because file names or paths...
	//can have spaces and my input function relies on cin. The result is that my function would only return the part...
	//of the user's input before the first space instead of the full name/path. The function getline avoids this.
	std::getline(std::cin, name);

	//filePath will ultimately contain the exact address of the file.
	std::string filePath;
	
	if (name != "")	//vets input
	{
		//If the name doesn't end with a .env it is added on to the end and also makes...
		//sure the name.substr(name.size() - 4, 4) part doesnt try to access a substring bigger than the string.
		if (name.size() > 4 && name.substr(name.size() - 4, 4) != ".env")
			name += ".env";
		else if (name.size() < 4)
			name += ".env";

		//If the name starts with "C:\" it indicates that the name is actually the full filepath.
		if (!(name[0] == 'C' && name[1] == ':' && name[2] == '\\'))
		{
			//If the name isn't a full filepath, and is thus just the filename:
			for (size_t i = 0; i < name.size(); i++)
			{
				//Checks name for invalid filename characters, if found, function returns false
				if (name[i] == '<' || name[i] == '>' || name[i] == '?' || name[i] == '|' || name[i] == '/' || name[i] == '\\' || name[i] == ':' || name[i] == '\"' || name[i] == '*')
				{
					std::cout << "Invalid file, exiting" << std::endl;
					Sleep(1000);
					return false;
				}
			}

			//If the user simply inputs a filename then the file is assumed to reside within the same..
			//directory as the program. This directory was saved to "programPath" near the beginning of the program.
			//char back is set to the last char in string program path
			char back = programPath.back();

			//The loop checks to see if the last char (char back) in program path is a faward slash.
			//If (char back) is not a foward slash then the last char in program path is erased and...
			//(char back) is set once again to the new last char in programPath.
			while (back != '\\')
			{
				programPath.erase(programPath.size() - 1);
				back = programPath.back();
			}

			//By deleting all the chars off the back of program path until hitting a foward slash...
			//we reduce the programPath from something like:
				//"C:\Users\conno\Documents\Visual Studio 2017\Projects\SHN-Sim\Debug\SHM-Sim.exe"
			//to the directory the program is in:
				//"C:\Users\conno\Documents\Visual Studio 2017\Projects\SHN-Sim\Debug\"
			filePath = programPath + name;
			//Thus: the ultimate filepath becomes the reduced programPath + the name the user inputted.
		}
		else
			//If the name IS a full filepath then the ultimate filepath is set to the name.
			filePath = name;



		//After determining the correct filepath the program is free to try and read the specified file...
		//FileIO::readSaveFileToENV() reads the .env file to the current program state.
		return FileIO::readSaveFileToENV(filePath);
	}
	else
	{
		//input vetting
		std::cout << "Invalid file, exiting" << std::endl;
		Sleep(1000);
		return false;
	}

}

//saveToFile attempts to save a .env file to a user inputted name or location&name
bool saveToFile()
{
	//prompts user for filename/path+name
	std::cout << std::endl << "Enter filename you wish to save under:" << std::endl;

	//The string "name" is the container for the user input, it is deliberately...
	//set to an empty string in case the user decides to hit enter without entering anything...
	//thus vetting the input.
	std::string name = "";

	//Here I use getline instead of my typical user input function UserIO::userInput() because file names or paths...
	//can have spaces and my input function relies on cin. The result is that my function would only return the part...
	//of the user's input before the first space instead of the full name/path. The function getline avoids this.
	std::getline(std::cin, name);

	//filePath will ultimately contain the exact address of the file.
	std::string filePath;

	if (name != "")	//vets input
	{
		//If the name doesn't end with a .env it is added on to the end and also makes...
		//sure the name.substr(name.size() - 4, 4) part doesnt try to access a substring bigger than the string.
		if (name.size() >= 4 && name.substr(name.size() - 4, 4) != ".env")
			name += ".env";
		else if (name.size() < 4)
			name += ".env";

		//Goes through each character of the string
		for (size_t i = 0; i < name.size(); i++)
		{
			//Checks name for invalid filename characters, if found, function returns false
			if (name[i] == '<' || name[i] == '>' || name[i] == '?' || name[i] == '|' || name[i] == '/' || name[i] == '\\' || name[i] == ':' || name[i] == '\"' || name[i] == '*')
			{
				std::cout << "Invalid file, exiting" << std::endl;
				Sleep(1000);
				return false;
			}
		}

		//If the user simply inputs a filename then the file is assumed to reside within the same..
		//directory as the program. This directory was saved to "programPath" near the beginning of the program.
		//char back is set to the last char in string program path
		char back = programPath.back();

		//The loop checks to see if the last char (char back) in program path is a faward slash.
		//If (char back) is not a foward slash then the last char in program path is erased and...
		//(char back) is set once again to the new last char in programPath.
		while (back != '\\')
		{
			programPath.erase(programPath.size() - 1);
			back = programPath.back();
		}
		//By deleting all the chars off the back of program path until hitting a foward slash...
		//we reduce the programPath from something like:
		//"C:\Users\conno\Documents\Visual Studio 2017\Projects\SHN-Sim\Debug\SHM-Sim.exe"
		//to the directory the program is in:
		//"C:\Users\conno\Documents\Visual Studio 2017\Projects\SHN-Sim\Debug\"

		filePath = programPath + name;
		//Thus: the ultimate filepath becomes the reduced programPath + the name the user inputted.

		//After determining the correct filepath the program is free to try and read the specified file...
		//FileIO::writeSaveFileFromENV() writes the .env file from the current program state.
		return FileIO::writeSaveFileFromENV(filePath);
	}
	else
	{
		//input vetting
		std::cout << "Invalid file, exiting" << std::endl;
		Sleep(1000);
		return false;
	}
}

bool environmentTick()
{
	/*
	for each BaseStation in BaseStationList
	{
		if (!BaseStationlist[BaseStation].Update())
			return false;
	}*/

	// move through each BaseStation in BaseStationList
	for (int bStation = 0; bStation < numberOfBaseStations; bStation++) {

		// returns false if the update function in the BaseStation class
		// returns false, which means it has not successfully updated
		if (!BaseStationList[bStation].Update()) { return false; } 

	}

	return true;
}

bool managerTick()
{

	return true;
}

void runSimulation()
{
	while (environmentTick() && managerTick())
	{
		envClock++;
	}
}
