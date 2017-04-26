#include "Manager.h"
#include "Simulation.h"
#include <Windows.h>

#define numagents 10
#define maxturns 50
#define pricehistorylength 10

using namespace std;

void Manager::Run()
{
	worldObject->Initialize(numagents, pricehistorylength);

	worldObject->Run(maxturns);
}

Manager::Manager()
{
	worldObject = Simulation::GetSimulationObject();
}


Manager::~Manager()
{
}