#include "Agent.h"
#include "Simulation.h"
#include <iostream>

#pragma once

Simulation;

using namespace std;

void Agent::AgentPrint()
{
	cout << "\nAgent ID#: " << agentIDNumber;
	cout << "\nAgent Type: " << agentType;
	cout << "\nAgent Intelligence: " << agentIntelligence;
	cout << "\nAgent NegotiateSkill: " << agentNegotiatingSkill;
	cout << "\nAgent Money: " << agentMoney;
	cout << "\nAgent Initial Money: " << agentInitialMoney;
	cout << "\n";
}

void Agent::Execute()
{
	initialTrade();
	evaluateOptions();
	
}

void Agent::TradeWith()
{
}

double Agent::ShareOfMoney(double worldMoney)
{
	return 0.0;
}

void Agent::initialTrade()
{
}

void Agent::produceFood()
{
}

void Agent::produceProduction()
{
}

void Agent::produceLuxury()
{
}

void Agent::tradeAsTurn()
{
}

void Agent::evaluateOptions()
{
}

double Agent::priceFood()
{
	return 0.0;
}

double Agent::priceProduction()
{
	return 0.0;
}

double Agent::priceLuxury()
{
	return 0.0;
}

Agent::Agent()
{
}

Agent::Agent(int idNumber, int type, int intelligence, int startingMoney)
{
}

Agent::~Agent()
{
}
