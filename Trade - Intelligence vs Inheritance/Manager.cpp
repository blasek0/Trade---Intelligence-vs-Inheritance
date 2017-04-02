#include "Manager.h"
#include "Simulation.h"
#include <Windows.h>

using namespace std;

void Manager::Run()
{
	worldObject->Initialize(500);
	worldObject->Run();
}

Manager::Manager(char* filename)
{
	worldObject = Simulation::GetSimulationObject(filename);
}


Manager::~Manager()
{
	delete worldObject;
}
