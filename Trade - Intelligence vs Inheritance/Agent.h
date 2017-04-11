#pragma once
#include <fstream>

class Agent
{
public: //public variables
	int agentIDNumber;
	int numOfAgents;
	int agentType;
	int agentMoney;
	int agentInitialMoney;
	int agentIntelligence;
	int agentNegotiatingSkill;
	int turnOption;
	int agentFood;
	int agentProduction;
	int agentLuxury;
	char agentFile[100];
	std::fstream outfile;

public: //public functions
	void AgentPrint();
	void Execute();
	double PriceFood();
	double PriceProduction();
	double PriceLuxury();
	double ShareOfMoney();
	void WriteAgentState();

private: //private functions
	void InitialTrade();
	void ProduceFood();
	void ProduceProduction();
	void ProduceLuxury();
	void EvaluateOptions();

public: //Constructors and destructors
	Agent(int idNumber, int intelligence, int startingMoney, char* saveFile);
	~Agent();
};

