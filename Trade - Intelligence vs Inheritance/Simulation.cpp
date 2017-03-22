#include "Simulation.h"
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>


using namespace std;

Simulation * Simulation::GetSimulationObject()
{
	static Simulation *simulationObject = nullptr;
	if (simulationObject == nullptr)
	{
		simulationObject = new Simulation();
	}
	return simulationObject;
}

void Simulation::Initialize()
{

}

void Simulation::Run()
{

}

Simulation::Simulation()
{
}


Simulation::~Simulation()
{
}
