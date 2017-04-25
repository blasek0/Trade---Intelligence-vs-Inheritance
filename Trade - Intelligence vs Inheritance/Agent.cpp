#include "Agent.h"
#include "Market.h"
#include "Simulation.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdlib.h>

#pragma once
#pragma warning(disable:4996)

Simulation;

using namespace std;

//Primary turn function for agents
void Agent::Execute()
{
	//agentFood = (int)round(agentFood * 0.95);				//Food stocks decay
	//agentProduction = (int)round(agentProduction * 0.95);	//Production capabilities decay
	agentFood = agentFood - 1;
	if (agentFood < 1)
	{
		ProduceFood();
		return;
	}
	else
	{
		EvaluateOptions();										//Agents choose which option to perform
	}//Eats 1 food per turn
}

void Agent::InitialTrade()
{
}

void Agent::ProduceFood()
{
	int temp = agentFood;
	agentFood += Simulation::GetSimulationObject()->CreateRandomNumber(agentIntelligence, 10);
	temp = agentFood - temp;
	Simulation::GetSimulationObject()->worldFood += temp;
}

void Agent::ProduceProduction()
{
	int temp = agentProduction;
	agentProduction += Simulation::GetSimulationObject()->CreateRandomNumber(1, agentIntelligence);
	temp = agentProduction - temp;
	Simulation::GetSimulationObject()->worldProduction += temp;
}

void Agent::ProduceLuxury()
{
	int temp = agentLuxury;
	agentLuxury += Simulation::GetSimulationObject()->CreateRandomNumber(1, agentIntelligence);
	temp = agentLuxury - temp;
	Simulation::GetSimulationObject()->worldLuxury += temp;
}

void Agent::ProduceMoney()
{
	int temp = agentMoney;
	agentMoney = (int)(round((agentMoney*(100 + Simulation::GetSimulationObject()->CreateRandomNumber(3, 5 + agentIntelligence))/100.0)));
	temp = agentMoney - temp;
	Simulation::GetSimulationObject()->worldMoney += temp;
}

void Agent::EvaluateOptions()
{
	Simulation *simulationObject = Simulation::GetSimulationObject();
	int foodUtility;
	int productionUtility;
	int luxuryUtility;
	int moneyUtility;
	int maxUtility;
	foodUtility = 0;
	productionUtility = 0;
	luxuryUtility = 0;
	moneyUtility = 0;
	maxUtility = -1;

	foodUtility = Simulation::GetSimulationObject()->FoodUtility(round(((double)agentIntelligence + 10.0) / 2.0)) - Simulation::GetSimulationObject()->FoodUtility(agentFood);
	if (foodUtility > maxUtility)
	{
		turnOption = 1;
		maxUtility = foodUtility;
	}

	productionUtility = simulationObject->ProductionUtility(round(((double)agentIntelligence + 1.0) / 2.0));
	if (productionUtility > maxUtility)
	{
		turnOption = 2;
		maxUtility = productionUtility;
	}

	if ((ShareOfMoney() > 5 || agentIntelligence >= 4) && agentProduction > 15)
	{
		luxuryUtility = simulationObject->LuxuryUtility(round(((double)agentIntelligence + 1.0) / 2.0));
	}
	else
	{
		luxuryUtility = 0;
	}
	if (luxuryUtility > maxUtility)
	{
		turnOption = 3;
		maxUtility = luxuryUtility;
	}

	double temp = 0.0;
	temp = (agentMoney * (((100+(8 + agentIntelligence) / 2.0))/100.0)) - agentMoney;
	moneyUtility = simulationObject->MoneyUtility((int)temp);
	
	if (moneyUtility > maxUtility)
	{
		//turnOption = 4;
		maxUtility = moneyUtility;
	}

	switch (turnOption)
	{
	case 1:
		ProduceFood();
		break;
	case 2:
		ProduceProduction();
		break;
	case 3:
		ProduceLuxury();
		break;
	case 4:
		ProduceMoney();
		break;
	default:
		ProduceFood();
		break;
	}
}

double Agent::ShareOfMoney()
{
	return (agentMoney / Simulation::GetSimulationObject()->worldMoney * 100.0);
}

void Agent::WriteAgentState()
{
	if (!outfile.is_open())
	{
		outfile.open(agentFile, ios::app);
	}
	if (outfile.fail())
	{
		cout << "failed to open file\n";
		system("pause");
	}
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

void Agent::WriteInitialState()
{
	char* toWrite = new char[100];
	char* temp = new char[65];
	if (!outfile.is_open())
	{
		outfile.open(agentFile, ios::out, ios::trunc);
	}
	if (outfile.fail())
	{
		cout << "\nFailed to initially open file, " << agentFile;
	}
	strcpy(toWrite, "Agent#, Intelligence, Initial Money, \n");
	outfile.write(toWrite, strlen(toWrite));
	strcpy(temp, "");
	strcpy(toWrite, "");
	itoa(agentIDNumber, temp, 10);
	strcat(temp, ", ");
	strcat(toWrite, temp);
	strcpy(temp, "");
	itoa(agentIntelligence, temp, 10);
	strcat(temp, ", ");
	strcat(toWrite, temp);
	strcpy(temp, "");
	itoa(agentInitialMoney, temp, 10);
	strcat(temp, ", ");
	strcat(toWrite, temp);
	outfile.write(toWrite, strlen(toWrite));
	strcpy(toWrite, "\nFood, Production, Luxury, Money, Turn Number, \n");
	outfile.write(toWrite, strlen(toWrite));
	outfile.close();
	delete temp;
	delete toWrite;
}

Agent::Agent(int idNumber, int intelligence, int startingMoney, char* saveFile)
{
	numOfAgents = Simulation::GetSimulationObject()->numOfAgents;
	agentIDNumber = idNumber;
	agentFood = 3;
	agentProduction = 1;
	agentLuxury = 1;
	agentMoney = startingMoney;
	Simulation::GetSimulationObject()->worldFood += agentFood;
	Simulation::GetSimulationObject()->worldProduction += agentProduction;
	Simulation::GetSimulationObject()->worldLuxury += agentLuxury;
	Simulation::GetSimulationObject()->worldMoney += agentMoney;
	agentInitialMoney = startingMoney;
	agentIntelligence = Simulation::GetSimulationObject()->CreateRandomNumber(1, 5);
	strcpy(agentFile, saveFile);
	char* temp = new char[20];
	itoa(agentIDNumber, temp, 10);
	strcat(agentFile, temp);
	strcat(agentFile, ".txt");
	delete temp;
	utilities.resize(5);
	for (int i = 0; i < 5; i++)
	{
		utilities[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			utilities[i][j] = 0;
		}
	}
	WriteInitialState();
}

Agent::Agent(const Agent & tempAgent)
{
	numOfAgents = tempAgent.numOfAgents;
	agentIDNumber = tempAgent.agentIDNumber;
	agentFood = tempAgent.agentFood;
	agentProduction = tempAgent.agentProduction;
	agentLuxury = tempAgent.agentLuxury;
	agentInitialMoney = tempAgent.agentInitialMoney;
	agentMoney = tempAgent.agentMoney;
	agentIntelligence = tempAgent.agentIntelligence;
	strcpy(agentFile, tempAgent.agentFile);
	utilities.resize(5);
	for (int i = 0; i < 5; i++)
	{
		utilities[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			utilities[i][j] = 0;
		}
	}
}

Agent::~Agent()
{
}
