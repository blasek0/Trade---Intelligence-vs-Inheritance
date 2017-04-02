#pragma once
class Agent
{
public: //public variables
	int agentIDNumber;
	int agentType;
	double agentMoney;
	double agentInitialMoney;
	int agentIntelligence;
	int agentNegotiatingSkill;
	int turnOption;
	int agentFood;
	int agentProduction;
	int agentLuxury;

public: //public functions
	void AgentPrint();
	void Execute();
	void TradeWith();
	double ShareOfMoney(double worldMoney);

private: //private functions
	void initialTrade();
	void produceFood();
	void produceProduction();
	void produceLuxury();
	void tradeAsTurn();
	void evaluateOptions();
	double priceFood();
	double priceProduction();
	double priceLuxury();

public: //Constructors and destructors
	Agent();
	Agent(int idNumber, int type, int intelligence, int startingMoney);
	~Agent();
};

