#pragma once
#include "Simulation.h"

class Manager
{
public:
	void Run();
	Simulation *worldObject;
	Manager(char* filename);
	~Manager();
};

