#pragma once
#include "Agent.h"
#include <vector>

class Simulation
{
private: //Private Variables

public:
	int worldMoney;
	int worldFood;
	int worldProduction;
	int worldLuxury;
	int numOfAgents;
	int turnNumber;
	char saveFile[100];
	int maxTurns;
	std::vector<Agent> AgentList;

public: //Public Functions
	static Simulation* GetSimulationObject();
	void Initialize(int numAgents);
	void Run(int numTurns);
	int CreateRandomNumber(int minValue, int maxValue);
	int CreateNormalNumber(double mean, double stddev);
	int foodUtility(int food);
	int productionUtility(int production);
	int luxuryUtility(int luxury);

private: //Private Functions
	void PrintWorldState();
	void WriteWorldState();

private: //Constructor
	Simulation();

public: //Destructor
	~Simulation();
};

