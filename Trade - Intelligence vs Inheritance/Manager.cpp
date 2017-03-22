#include "Manager.h"
#include "Simulation.h"
#include <Windows.h>

using namespace std;

void Manager::Run()
{
	worldObject->Initialize();
	worldObject->Run();
}

Manager::Manager()
{
	worldObject = Simulation::GetSimulationObject();
}


Manager::~Manager()
{
}
