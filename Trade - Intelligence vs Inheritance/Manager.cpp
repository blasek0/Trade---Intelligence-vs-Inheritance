#include "Manager.h"
#include "Simulation.h"
#include <Windows.h>

#define numagents 500
#define maxturns 500
#define pricehistorylength 2

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