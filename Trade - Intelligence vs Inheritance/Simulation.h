#pragma once
#include "Cell.h"
#include "Agent.h"
#include <vector>
#include <stdlib.h>

class Simulation
{
public:
	static Simulation* GetSimulationObject();
	void Initialize();
	void Run();

private:
	Simulation();

public:
	~Simulation();
};

