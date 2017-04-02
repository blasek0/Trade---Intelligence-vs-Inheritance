#pragma once
#include "Agent.h"
#include <vector>

class Simulation
{
private: //Private Variables
	double worldMoney;
	int numOfAgents;
	std::vector<Agent> AgentList;
	char SaveFile[65];

public: //Public Functions
	static Simulation* GetSimulationObject(char* filename);
	void Initialize(int numAgents);
	void Run();
	int CreateRandomNumber(int minValue, int maxValue);
	int CreateNormalNumber(double mean, double stddev);
	Agent TradeWithAgent(unsigned int agentNumber);

private: //Private Functions
	void PrintWorldState();
	void WriteWorldState();

private: //Constructor
	Simulation(char* filename);

public: //Destructor
	~Simulation();
};

