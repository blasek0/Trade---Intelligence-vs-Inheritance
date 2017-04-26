#pragma once
#include <fstream>
#include <stdlib.h>
#include <vector>

class Agent
{
public: //public variables
	int agentIDNumber;
	int numOfAgents;
	double agentMoney;
	int agentInitialMoney;
	int agentIntelligence;
	int agentNegotiatingSkill;
	int turnOption;
	int agentFood;
	int agentProduction;
	int agentLuxury;
	char agentFile[20];
	std::fstream outfile;

public: //public functions
	void Execute();
	double ShareOfMoney();
	void WriteAgentState();
	void WriteInitialState();

private: //private functions
	void Trade();
	void ProduceFood();
	void ProduceProduction();
	void ProduceLuxury();
	void ProduceMoney();
	void EvaluateOptions();

public: //Constructors and destructors
	Agent(int idNumber, int startingMoney, char* saveFile);
	Agent(const Agent &tempAgent);
	~Agent();
};