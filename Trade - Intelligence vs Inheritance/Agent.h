#pragma once
#include <fstream>
#include <stdlib.h>
#include <vector>

class Agent
{
public: //public variables
	int agentIDNumber;
	int numOfAgents;
	double foodConfidenceInterval;
	double productionConfidenceInterval;
	double luxuryConfidenceInterval;
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
	void FailedFoodBid(double price);
	void FailedProductionBid(double price);
	void FailedLuxuryBid(double price);
	void SuccessfulFoodBid(double price);
	void SuccessfulProductionBid(double price);
	void SuccessfulLuxuryBid(double price);
	double GetFoodConfidence();
	double GetProductionConfidence();
	double GetLuxuryConfidence();

private: //private functions
	void Trade();
	void TradeFood();
	void TradeProduction();
	void TradeLuxury();
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