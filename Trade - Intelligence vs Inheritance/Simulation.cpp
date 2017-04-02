#include "Simulation.h"
#include "Agent.h"
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#pragma once
#pragma warning(disable: 4996)

Agent;

using namespace std;

Simulation * Simulation::GetSimulationObject(char* filename)
{
	static Simulation *simulationObject = nullptr;
	if (simulationObject == nullptr)
	{
		simulationObject = new Simulation(filename);
	}
	return simulationObject;
}

void Simulation::Initialize(int numAgents)
{
	
}

void Simulation::Run()
{

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

Agent Simulation::TradeWithAgent(unsigned int agentNumber)
{	//Returns pointer to the requested agent
	return AgentList[agentNumber-1];
}

void Simulation::PrintWorldState()
{

}

void Simulation::WriteWorldState()
{
	fstream outfile;
	outfile.open(SaveFile);

	outfile.close();
}

Simulation::Simulation(char* filename)
{
	strcpy(SaveFile, filename);
	AgentList.resize(0);
}


Simulation::~Simulation()
{

}
