#include "Agent.h"
#include "Simulation.h"
#include <iostream>
#include <cmath>
#include <fstream>

#pragma once
#pragma warning(disable:4996)

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

//Primary turn function for agents
void Agent::Execute()
{
	agentFood = (int)round(agentFood * 0.95);				//Food stocks decay
	agentProduction = (int)round(agentProduction * 0.95);	//Production capabilities decay
	if (agentFood < 1)
	{
		ProduceFood();
		return;
	}
	agentFood = agentFood - 1;								//Eats 1 food per turn
	InitialTrade();											//Agents trade with surroundings
	EvaluateOptions();										//Agents choose which option to perform
}

double Agent::ShareOfMoney()
{
	return ((double)agentMoney / (double)Simulation::GetSimulationObject()->worldMoney * 100.0);
}

void Agent::WriteAgentState()
{
	fstream outfile;
	char* temp = new char[65];
	itoa(agentFood, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(agentProduction, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(agentLuxury, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(agentMoney, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(Simulation::GetSimulationObject()->turnNumber, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	outfile.write("\n", 1);
	delete temp;
}

void Agent::InitialTrade()
{
	if (agentFood <= 0) return;
	Simulation *simulationObject = Simulation::GetSimulationObject();
	int temp[5] = { 0, 0, 0, 0, 0 };
	for (int i = 0; i < 5; i++)
	{
		temp[i] = simulationObject->CreateRandomNumber(1, numOfAgents);
	}

	for (int i = 0; i < 5; i++)
	{
		
	}
}

void Agent::ProduceFood()
{
	agentFood += Simulation::GetSimulationObject()->CreateRandomNumber(agentIntelligence, 10);
}

void Agent::ProduceProduction()
{
	agentProduction += Simulation::GetSimulationObject()->CreateRandomNumber(1, agentIntelligence);
}

void Agent::ProduceLuxury()
{	//Currently unused
}

void Agent::EvaluateOptions()
{
	Simulation *simulationObject = Simulation::GetSimulationObject();
	int foodUtility;
	int productionUtility;
	int luxuryUtility;
	foodUtility = 0;
	productionUtility = 0;
	luxuryUtility = 0;
	for (int i = 1; i < round(((double)agentIntelligence + 10.0) / 2.0)+1; i++)
	{
		foodUtility += simulationObject->foodUtility(agentFood + i);
	}
	for (int i = 1; i < round(((double)agentIntelligence + 1) / 2.0)+1; i++)
	{
		productionUtility += simulationObject->productionUtility(agentProduction + i);
	}
	if (foodUtility > productionUtility)
	{
		ProduceFood();
	}
	else
	{
		ProduceProduction();
	}
}

double Agent::PriceFood()
{
	return 0.0;
}

double Agent::PriceProduction()
{
	return 0.0;
}

double Agent::PriceLuxury()
{
	return 0.0;
}

Agent::Agent(int idNumber, int intelligence, int startingMoney, char * saveFile)
{
	numOfAgents = Simulation::GetSimulationObject()->numOfAgents;
	agentIDNumber = idNumber;
	agentFood = 3;
	agentProduction = 0;
	agentLuxury = 0;
	agentMoney = startingMoney;
	Simulation::GetSimulationObject()->worldMoney += agentMoney;
	agentInitialMoney = startingMoney;
	agentNegotiatingSkill = 0;
	agentIntelligence = Simulation::GetSimulationObject()->CreateRandomNumber(1, 5);
	strcpy(agentFile, saveFile);
	char* toWrite = new char[250];
	char* temp = new char[65];
	itoa(agentIDNumber, temp, 10);
	strcat(agentFile, temp);
	strcat(agentFile, ".txt");
	outfile.open(agentFile, ios::app);
	outfile.write("Agent#, ", 8);
	outfile.write("Intelligence, ", 14);
	outfile.write("Initial Money, ", 15);
	outfile.write("Negotiating Skill, ", 19);
	outfile.write("\n", 1);
	strcpy(temp, "");
	strcpy(toWrite, "");
	itoa(agentIDNumber, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(agentIntelligence, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(agentInitialMoney, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(agentNegotiatingSkill, temp, 10);
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
	delete temp;
}

Agent::~Agent()
{
}
