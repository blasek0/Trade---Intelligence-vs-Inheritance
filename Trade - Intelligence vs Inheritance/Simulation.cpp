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
#include <sstream>

#pragma once
#pragma warning(disable: 4996)

#define filename "Agent"
#define turnstosave 50

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
	fstream outfile;
	numOfAgents = numAgents;
	int tempVar, tempVarTwo;
	for (int i = 0; i < numOfAgents; i++)
	{
		tempVar = CreateRandomNumber(1, 5);
		tempVarTwo = CreateRandomNumber(1, 100);
		if (tempVarTwo % 50 == 0)
		{
			Agent *thisAgent = new Agent(i + 1, tempVar, 1000*(CreateRandomNumber(1, 5)), filename);
			AgentList.push_back(*thisAgent);
		}
		else
		{
			Agent *thisAgent = new Agent(i + 1, tempVar, 10 * (CreateRandomNumber(1, 5)), filename);
			AgentList.push_back(*thisAgent);
		}
	}
	char* temp = new char[65];
/*	for (int i = 1; i < numOfAgents+1; i++)
	{
		itoa(i, temp, 10);
		strcpy(saveFile, filename);
		strcat(saveFile, temp);
		strcat(saveFile, ".txt");
		outfile.open(saveFile, ios::app);
		outfile.write("Agent#, ", 8);
		outfile.write("Intelligence, ", 14);
		outfile.write("Initial Money, ", 15);
		outfile.write("Negotiating Skill, ", 19);
		outfile.write("\n", 1);
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentIDNumber, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentIntelligence, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentInitialMoney, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentNegotiatingSkill, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		outfile.write("\n", 1);
		outfile.write("Food, ", 6);
		outfile.write("Production, ", 12);
		outfile.write("Luxury, ", 8);
		outfile.write("Money, ", 7);
		outfile.write("Turn Number, ", 13);
		outfile.write("\n", 1);

		outfile.close();
	}
	*/
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
			//WriteWorldState();
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

int Simulation::CreateNormalNumber(double mean, double stddev)
{	//Currently unused
	
	return 0;
}

int Simulation::foodUtility(int food)
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

int Simulation::productionUtility(int production)
{
	return 5;
}

int Simulation::luxuryUtility(int luxury)
{
	return 0;
}

void Simulation::PrintWorldState()
{	//Currently unused
	
}

void Simulation::WriteWorldState()
{
	fstream outfile;
	char* temp = new char[65];
	for (int i = 1; i < numOfAgents+1; i++)
	{
		itoa(i, temp, 10);
		strcpy(saveFile, filename);
		strcat(saveFile, temp);
		strcat(saveFile, ".txt");
		outfile.open(saveFile, ios::app);
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentFood, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentProduction, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentLuxury, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(AgentList[i - 1].agentMoney, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		strcpy(temp, "");
		itoa(turnNumber, temp, 10);
		strcat(temp, ", ");
		outfile.write(temp, strlen(temp));
		outfile.write("\n", 1);

		outfile.close();
	}
	delete temp;
}

Simulation::Simulation()
{
	AgentList.clear();
	turnNumber = 0;
	worldMoney = 0;
	numOfAgents = 0;
	strcpy(saveFile, "");
	maxTurns = 0;
}


Simulation::~Simulation()
{
}
