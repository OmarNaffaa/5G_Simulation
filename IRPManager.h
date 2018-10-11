#pragma once
#include <iostream> 
#include <Windows.h>
#include "IRPManager.h"

class BaseStation;
class AreaUnit;

class IRPManager
{
protected:
	int objID;
	int time;

public:
	IRPManager();

	void initializeVars(int);

	int getObjID();

	int getTime();

	void incrementTime();

	void incrementTime(int);

	void IRP_OperatingSystem();

	void updateEnvironment();

	void triggerMonitoringFunctionInBaseStations();

	int** analyzeBaseStationTCOSHReports();

	void identifyFault();
	void reportsFault();
	void KPIGapAnalysis();
	void storeDataAndLearn();
	void identifySeverity();
	void compensationProcedures();
	void faultRepair();
	void reevaluateFault();
	void logAndReport();
};
