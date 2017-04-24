#include "Simulation.h"
#include "Agent.h"
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <cstring>
#include <string>

#pragma once
#pragma warning(disable: 4996)

#define filename "Agent"
#define turnstosave 10

Agent;

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

void Simulation::Initialize(int numAgents)
{
	numOfAgents = numAgents;
	int tempVar, tempVarTwo;
	char* temp = new char[65];
	strcpy(temp, filename);
	for (int i = 0; i < numOfAgents; i++)
	{
		tempVar = CreateRandomNumber(1, 5);
		tempVarTwo = CreateRandomNumber(1, 100);
		if (tempVarTwo % 50 == 0)
		{
			Agent *thisAgent = new Agent(i + 1, tempVar, CreateRandomNumber(1000, 10000), temp);
			AgentList.push_back(*thisAgent);
		}
		else
		{
			Agent *thisAgent = new Agent(i + 1, tempVar, CreateRandomNumber(10, 50), temp);
			AgentList.push_back(*thisAgent);
		}
	}
	delete temp;
}

void Simulation::Run(int numTurns)
{
	maxTurns = numTurns;
	//Execution code goes here
	for (turnNumber = 1; turnNumber <= maxTurns; turnNumber++)
	{
		for (int z = 0; z < numOfAgents; z++)
		{
			//cout << AgentList[i].agentIDNumber;
			AgentList[z].Execute();
		}
		if (turnNumber % turnstosave == 0)
		{
			for (int i = 0; i < numOfAgents; i++)
			{
				AgentList[i].WriteAgentState();
			}
		}
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
			return 75;
		case 3: 
			return 50;
		case 4:
			return 25;
		case 5:
			return 10;
		case 6:
			return 5;
		default:
			return 1;
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

Simulation::Simulation()
{
	AgentList.clear();
	turnNumber = 0;
	worldMoney = 0;
	worldFood = 0;
	worldProduction = 0;
	worldLuxury = 0;
	numOfAgents = 0;
	strcpy(saveFile, "");
	maxTurns = 0;
}


Simulation::~Simulation()
{
	AgentList.clear();
}
