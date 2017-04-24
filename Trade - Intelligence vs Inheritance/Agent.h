#pragma once
#include <fstream>
#include <stdlib.h>
#include <vector>

class Agent
{
public: //public variables
	int agentIDNumber;
	int numOfAgents;
	int agentMoney;
	int agentInitialMoney;
	int agentIntelligence;
	int turnOption;
	int agentFood;
	int agentProduction;
	int agentLuxury;
	char agentFile[20];
	std::fstream outfile;
	std::vector<std::vector<int>> utilities;

public: //public functions
	void Execute();
	int PriceFood();
	int PriceProduction();
	int PriceLuxury();
	double ShareOfMoney();
	void WriteAgentState();
	void WriteInitialState();

private: //private functions
	void InitialTrade();
	void ProduceFood();
	void ProduceProduction();
	void ProduceLuxury();
	void ProduceMoney();
	void EvaluateOptions();

public: //Constructors and destructors
	Agent(int idNumber, int intelligence, int startingMoney, char* saveFile);
	Agent(const Agent &tempAgent);
	~Agent();
};

