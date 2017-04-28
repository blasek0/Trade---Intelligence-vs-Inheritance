#include "Simulation.h"
#include "Agent.h"
#include "Market.h"
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <cstring>
#include <string>
#include <math.h>

#pragma once
#pragma warning(disable: 4996)

#define filename "Agent"
#define turnstosave 10

Agent;
Market;

using namespace std;

Simulation * Simulation::GetSimulationObject()
{
	static Simulation *simulationObject = nullptr;
	if (simulationObject == nullptr)
	{
		simulationObject = new Simulation();
	}
	return simulationObject;
}

double Simulation::GetPrice(double buyPrice, double sellPrice, int buyingAgent, int sellingAgent)
{
	double moneyDifference = AgentList[sellingAgent - 1].ShareOfMoney() - AgentList[buyingAgent - 1].ShareOfMoney();
	int negotiatingSkillDifference = AgentList[sellingAgent - 1].agentNegotiatingSkill - AgentList[buyingAgent - 1].agentNegotiatingSkill;
	int intelligenceDifference = AgentList[sellingAgent - 1].agentIntelligence - AgentList[buyingAgent - 1].agentIntelligence;
	double priceFactor = moneyDifference + 10 * negotiatingSkillDifference + 2 * intelligenceDifference;
	if (priceFactor > 50) priceFactor = 50;
	if (priceFactor < -50) priceFactor = -50;
	return (((buyPrice + sellPrice) / 2.0) * ((100.0+priceFactor)/100.0));
}

double Simulation::GetPriceBelief(double price, double confidenceInterval)
{
	if (price == 0)
	{
		return (1 * ((CreateRandomNumber(50 + confidenceInterval, 150 - confidenceInterval)) / 100.0));
	}
	else
	{
		return (price * ((CreateRandomNumber(50 + confidenceInterval, 150 - confidenceInterval)) / 100.0));
	}
}

void Simulation::Initialize(int numAgents, int turnsToAvg)
{
	marketObject->turnsToAvg = turnsToAvg;
	numOfAgents = numAgents;
	int tempVar;
	char* temp = new char[255];
	strcpy(temp, filename);
	for (int i = 0; i < numOfAgents; i++)
	{
		tempVar = CreateRandomNumber(1, 100);
		if (tempVar % 50 == 0)
		{
			Agent *thisAgent = new Agent(i + 1, CreateRandomNumber(1000, 10000), temp);
			AgentList.push_back(*thisAgent);
		}
		else
		{
			Agent *thisAgent = new Agent(i + 1, CreateRandomNumber(10, 50), temp);
			AgentList.push_back(*thisAgent);
		}
	}
	strcpy(worldFile, "WorldSummary.txt");
	strcpy(temp, "Food, Production, Luxury, Money, Turn Number, \n");
	outfile.open(worldFile, ios::out, ios::trunc);
	outfile.write(temp, strlen(temp));
	outfile.close();
	delete temp;
}

void Simulation::Run(int numTurns)
{
	maxTurns = numTurns;
	for (turnNumber = 1; turnNumber <= maxTurns; turnNumber++)
	{
		for (int z = 0; z < numOfAgents; z++)
		{
			AgentList[z].Execute();
		}
		if (turnNumber % turnstosave == 0)
		{
			for (int i = 0; i < numOfAgents; i++)
			{
				AgentList[i].WriteAgentState();
			}
			marketObject->WriteMarketState();
			WriteWorldState();
		}
		marketObject->SortMarkets();
		marketObject->ResolveBooks();
	}
}

int Simulation::CreateRandomNumber(int minValue, int maxValue)
{
	int temp = minValue + (rand() % (maxValue - minValue + 1));
	while (temp < minValue || temp > maxValue)
	{
		temp = minValue + (rand() % (maxValue - minValue + 1));
	}
	return temp;
}

int Simulation::FoodUtility(int food)
{
	switch (food)
	{
		case 1:
			return 100;
		case 2:
			return 175;
		case 3: 
			return 225;
		case 4:
			return 250;
		case 5:
			return 260;
		case 6:
			return 265;
		default:
			return 259+food;
	}
}

int Simulation::ProductionUtility(int production)
{
	return 5*production;
}

int Simulation::LuxuryUtility(int luxury)
{
	return 25*luxury;
}

int Simulation::MoneyUtility(int money)
{
	return 1 * money;
}

void Simulation::WriteWorldState()
{
	char* temp = new char[255];
	if (!outfile.is_open())
	{
		outfile.open(worldFile, ios::app);
	}
	strcpy(temp, "");
	itoa(worldFood, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(worldProduction, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(worldLuxury, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(worldMoney, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(turnNumber, temp, 10);
	strcat(temp, ", \n");
	outfile.write(temp, strlen(temp));
	delete temp;
}

Simulation::Simulation()
{
	srand(time(NULL));
	AgentList.clear();
	turnNumber = 0;
	worldMoney = 0;
	worldFood = 0;
	worldProduction = 0;
	worldLuxury = 0;
	numOfAgents = 0;
	strcpy(saveFile, "");
	maxTurns = 0;
	marketObject = new Market();
}


Simulation::~Simulation()
{
	AgentList.clear();
}