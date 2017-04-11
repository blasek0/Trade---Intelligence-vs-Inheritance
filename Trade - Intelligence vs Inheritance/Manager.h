#pragma once
#include "Simulation.h"

class Manager
{
public:
	Simulation *worldObject;
	void Run();
	Manager();
	~Manager();
};

