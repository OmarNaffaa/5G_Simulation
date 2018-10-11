#include "IRPManager.h"


IRPManager::IRPManager()
{
	;
}

/*IRPManager::IRPManager(int a_n, int a_row, int a_col, int a_numberOfBaseStations, int a_objectCount, AreaUnit** a_env, BaseStation* a_BaseStationList)
{
	this->time = 0;
	this->objID = a_n;
	this->env = a_env;
	this->BaseStationList = a_BaseStationList;
	this->row = a_row;
	this->col = a_col;
	this->numberOfBaseStations = a_numberOfBaseStations;
	this->objectCount = a_objectCount;
}*/

void IRPManager::initializeVars(int a_n)
{
	this->time = 0;
	this->objID = a_n;
	
}

/*int** IRPManager::allocateBaseStationsArray(int numberOfBaseStations)
{
	int** placeholder = (int**)NULL;
	return placeholder;
}*/

int IRPManager::getObjID()
{
	return this->objID;
}
int IRPManager::getTime()
{
	return this->time;
}

void IRPManager::incrementTime()
{
	++(this->time);
}

void IRPManager::incrementTime(int n)
{
	(this->time) += n;
}

void IRPManager::IRP_OperatingSystem()
{
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER t1, t2;					// ticks
	double elapsedTime;

	while (true)
	{
		QueryPerformanceFrequency(&frequency);					//these lines start timer
		QueryPerformanceCounter(&t1);

		updateEnvironment();
		triggerMonitoringFunctionInBaseStations();
		int** faultReport = analyzeBaseStationTCOSHReports();
		if (faultReport[0][0])
		{
			identifyFault();
			reportsFault();				//tells BaseStation about fault, triggers diagnosis procedures in BaseStation
			KPIGapAnalysis();
			storeDataAndLearn();
			identifySeverity();
			compensationProcedures();
			faultRepair();				//triggers self healing/recovery of BaseStation
			reevaluateFault();			//checks BaseStation for initial fault, if not present clears alarm.
			logAndReport();				//creates log of fault, sends report to management system
		}

		QueryPerformanceCounter(&t2);		//stop timer
		elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;		//calculates elapsed time
		if (elapsedTime < 1000)
			Sleep((DWORD)(1000 - elapsedTime));										//make ticks happen every second
		incrementTime();
	}
}

void IRPManager::updateEnvironment()
{
	//updates entire environment to induce changes based off of typical conditions and chance fluctuations
}

void IRPManager::triggerMonitoringFunctionInBaseStations()
{
	//causes every BaseStation to engage in 1-1 & 1-2, respectively monitoring/comparing TCOSH
}

int** IRPManager::analyzeBaseStationTCOSHReports()
{
	//looks at tcosh reports, compares reported tcosh with the collected measurments
	//triggers alarm function in BaseStations where needed, supplies alarm code
	//ALLOCATES RETURN ARRAY 
	int** placeholder = (int**)NULL;
	return placeholder;
}

void IRPManager::identifyFault() { ; }
void IRPManager::reportsFault() { ; }
void IRPManager::KPIGapAnalysis() { ; }
void IRPManager::storeDataAndLearn() { ; }
void IRPManager::identifySeverity() { ; }
void IRPManager::compensationProcedures() { ; }
void IRPManager::faultRepair() { ; }
void IRPManager::reevaluateFault() { ; }
void IRPManager::logAndReport() { ; }