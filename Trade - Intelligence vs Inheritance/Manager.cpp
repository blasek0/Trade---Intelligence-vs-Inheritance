#include "Manager.h"
#include "Simulation.h"
#include <Windows.h>

#define numagents 1
#define maxturns 1

using namespace std;

void Manager::Run()
{
	worldObject->Initialize(numagents);

	worldObject->Run(maxturns);
}

Manager::Manager()
{
	worldObject = Simulation::GetSimulationObject();
}


Manager::~Manager()
{
}
