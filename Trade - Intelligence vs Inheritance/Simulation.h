#pragma once
#include "Agent.h"
#include "Market.h"
#include <vector>
#include <stdlib.h>
#include <fstream>

class Simulation
{
private: //Private Variables

public:
	double worldMoney;
	int worldFood;
	int worldProduction;
	int worldLuxury;
	int numOfAgents;
	int turnNumber;
	char saveFile[100];
	char worldFile[100];
	int maxTurns;
	std::fstream outfile;
	std::vector<Agent> AgentList;
	static Simulation* simulationObject;
	Market* marketObject;

public: //Public Functions
	static Simulation* GetSimulationObject();
	double GetPrice(double buyPrice, double sellPrice, int buyingAgent, int sellingAgent);
	double GetPriceBelief(double price, double confidenceInterval);
	void Initialize(int numAgents, int turnsToAvg);
	void Run(int numTurns);
	int CreateRandomNumber(int minValue, int maxValue);
	int FoodUtility(int food);
	int ProductionUtility(int production);
	int LuxuryUtility(int luxury);
	int MoneyUtility(int money);
	void WriteWorldState();

private: //Private Functions

private: //Constructor
	Simulation();

public: //Destructor
	~Simulation();
};