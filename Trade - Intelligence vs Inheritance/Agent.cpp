#include "Agent.h"
#include "Market.h"
#include "Simulation.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

#pragma once
#pragma warning(disable:4996)

Simulation;

using namespace std;

//Primary turn function for agents
void Agent::Execute()
{
	//cout << agentIDNumber << " Executing turn #: " << Simulation::GetSimulationObject()->turnNumber << "\n";
	foodConfidenceInterval -= 0.2;
	productionConfidenceInterval -= 0.2;
	luxuryConfidenceInterval -= 0.2;
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
		EvaluateOptions();									//Agents choose which option to perform
		Trade();
	}//Eats 1 food per turn
}

void Agent::Trade()
{
	TradeFood();
	TradeProduction();
	TradeLuxury();
}

void Agent::TradeFood()
{
	Simulation *tempPointer = Simulation::GetSimulationObject();
	double avgFood = (double)tempPointer->worldFood / (double)numOfAgents;
	double price = tempPointer->GetPriceBelief(tempPointer->marketObject->AvgFoodPrice(), foodConfidenceInterval);
	if ((double)agentFood > avgFood)
	{
		tempPointer->marketObject->CreateAsk(agentIDNumber, 1, price, (int)round(((double)agentFood - avgFood)));
		return;
	}
	else if (turnOption == 1 && agentFood > 3)
	{
		tempPointer->marketObject->CreateAsk(agentIDNumber, 1, price, (agentFood - 3));
		return;
	}
	else if ((int)round((avgFood - (double)agentFood) > 0))
	{
		tempPointer->marketObject->CreateBid(agentIDNumber, 1, price, (int)round((avgFood - (double)agentFood)));
		return;
	}
}

void Agent::TradeProduction()
{
	Simulation *tempPointer = Simulation::GetSimulationObject();
	double avgProduction = (double)tempPointer->worldProduction / (double)numOfAgents;
	double price = tempPointer->GetPriceBelief(tempPointer->marketObject->AvgProductionPrice(), productionConfidenceInterval);
	if ((double)agentProduction > avgProduction && agentProduction > 15)
	{
		tempPointer->marketObject->CreateAsk(agentIDNumber, 2, price, (agentProduction - 15));
		return;
	}
	else if (turnOption == 2 && agentProduction > 15 || agentProduction > 25)
	{
		tempPointer->marketObject->CreateAsk(agentIDNumber, 2, price, (agentProduction - 15));
		return;
	}
	else
	{
		tempPointer->marketObject->CreateBid(agentIDNumber, 2, price, 15 - agentProduction + 1);
		return;
	}
}

void Agent::TradeLuxury()
{
	Simulation *tempPointer = Simulation::GetSimulationObject();
	double avgLuxury = (double)tempPointer->worldProduction / (double)numOfAgents;
	double price = tempPointer->GetPriceBelief(tempPointer->marketObject->AvgLuxuryPrice(), luxuryConfidenceInterval);
	if ((double)agentLuxury > avgLuxury && (ShareOfMoney() > 5 || agentIntelligence >= 4) && agentProduction > 15)
	{
		tempPointer->marketObject->CreateAsk(agentIDNumber, 3, price, (int)avgLuxury - agentLuxury);
		return;
	}
	else
	{
		if (avgLuxury - agentLuxury > 0)
		{
			tempPointer->marketObject->CreateBid(agentIDNumber, 3, price, (int)avgLuxury - agentLuxury);
		}
		return;
	}
}

void Agent::ProduceFood()
{
	int temp = agentFood;
	if (agentProduction == 0)
	{
		agentFood += Simulation::GetSimulationObject()->CreateRandomNumber(agentIntelligence, 5);
	}
	else
	{
		agentFood += Simulation::GetSimulationObject()->CreateRandomNumber(agentIntelligence, 10);
	}
	temp = agentFood - temp;
	Simulation::GetSimulationObject()->worldFood += temp;
	if (Simulation::GetSimulationObject()->CreateRandomNumber(1, 4) == 4)
	{
		agentProduction--;
		Simulation::GetSimulationObject()->worldProduction--;
	}
}

void Agent::ProduceProduction()
{
	int temp = agentProduction;
	agentProduction += Simulation::GetSimulationObject()->CreateRandomNumber(1, agentIntelligence);
	temp = agentProduction - temp;
	Simulation::GetSimulationObject()->worldProduction += temp;
	agentFood -= 2;
	Simulation::GetSimulationObject()->worldFood -= 2;
}

void Agent::ProduceLuxury()
{
	int temp = agentLuxury;
	agentLuxury += Simulation::GetSimulationObject()->CreateRandomNumber(1, agentIntelligence);
	temp = agentLuxury - temp;
	Simulation::GetSimulationObject()->worldLuxury += temp;
	agentFood -= 2;
	agentProduction -= 5;
	Simulation::GetSimulationObject()->worldFood -= 2;
	Simulation::GetSimulationObject()->worldProduction -= 5;
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

	if (agentProduction > 0)
	{
		foodUtility = Simulation::GetSimulationObject()->FoodUtility(round(((double)agentIntelligence + 10.0) / 2.0)) - Simulation::GetSimulationObject()->FoodUtility(agentFood);
	}
	else
	{
		foodUtility = Simulation::GetSimulationObject()->FoodUtility(round(((double)agentIntelligence + 5.0) / 2.0)) - Simulation::GetSimulationObject()->FoodUtility(agentFood);
	}
	if (foodUtility > maxUtility)
	{
		turnOption = 1;
		maxUtility = foodUtility;
	}

	productionUtility = simulationObject->ProductionUtility(round(((double)agentIntelligence + 1.0) / 2.0));
	if (productionUtility > maxUtility && agentFood >= 2)
	{
		turnOption = 2;
		maxUtility = productionUtility;
	}

	if ((ShareOfMoney() > 5 || agentIntelligence >= 4) && agentProduction > 15 && agentFood >= 2)
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

	if (ShareOfMoney() > .1)
	{
		double temp = 0.0;
		temp = (agentMoney * (((100 + (8 + agentIntelligence) / 2.0)) / 100.0)) - agentMoney;
		moneyUtility = simulationObject->MoneyUtility((int)temp);
	}
	if (moneyUtility > maxUtility)
	{
		//turnOption = 4;
		//maxUtility = moneyUtility;
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
	strcpy(toWrite, "Agent#, Intelligence, Negotiating Skill, Initial Money, \n");
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
	itoa(agentNegotiatingSkill, temp, 10);
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

void Agent::FailedFoodBid(double price)
{
	foodConfidenceInterval--;
	if (foodConfidenceInterval < 0)
	{
		foodConfidenceInterval = 0;
	}
}

void Agent::FailedProductionBid(double price)
{
	productionConfidenceInterval--;
	if (productionConfidenceInterval < 0)
	{
		productionConfidenceInterval = 0;
	}
}

void Agent::FailedLuxuryBid(double price)
{
	luxuryConfidenceInterval--;
	if (luxuryConfidenceInterval < 0)
	{
		luxuryConfidenceInterval = 0;
	}
}

void Agent::SuccessfulFoodBid(double price)
{
	foodConfidenceInterval++;
	if (foodConfidenceInterval > 40)
	{
		foodConfidenceInterval = 40;
	}
}

void Agent::SuccessfulProductionBid(double price)
{
	productionConfidenceInterval++;
	if (productionConfidenceInterval > 40)
	{
		productionConfidenceInterval = 40;
	}
}

void Agent::SuccessfulLuxuryBid(double price)
{
	luxuryConfidenceInterval++;
	if (luxuryConfidenceInterval > 40)
	{
		luxuryConfidenceInterval = 40;
	}
}

double Agent::GetFoodConfidence()
{
	if (foodConfidenceInterval > 40.0)
	{
		return 40.0;
	}
	else if (foodConfidenceInterval < 0)
	{
		return 0.0;
	}
	return foodConfidenceInterval;
}

double Agent::GetProductionConfidence()
{
	if (productionConfidenceInterval > 40.0)
	{
		return 40.0;
	}
	else if (productionConfidenceInterval < 0)
	{
		return 0.0;
	}
	return productionConfidenceInterval;
}

double Agent::GetLuxuryConfidence()
{
	if (luxuryConfidenceInterval > 40.0)
	{
		return 40.0;
	}
	else if (luxuryConfidenceInterval < 0)
	{
		return 0.0;
	}
	return luxuryConfidenceInterval;
}

Agent::Agent(int idNumber, int startingMoney, char* saveFile)
{
	numOfAgents = Simulation::GetSimulationObject()->numOfAgents;
	agentIDNumber = idNumber;
	agentFood = Simulation::GetSimulationObject()->CreateRandomNumber(5, 15);
	agentProduction = Simulation::GetSimulationObject()->CreateRandomNumber(3, 8);
	agentLuxury = 1;
	agentMoney = startingMoney;
	foodConfidenceInterval = 0.0;
	productionConfidenceInterval = 0.0;
	luxuryConfidenceInterval = 0.0;
	Simulation::GetSimulationObject()->worldFood += agentFood;
	Simulation::GetSimulationObject()->worldProduction += agentProduction;
	Simulation::GetSimulationObject()->worldLuxury += agentLuxury;
	Simulation::GetSimulationObject()->worldMoney += agentMoney;
	agentInitialMoney = startingMoney;
	agentIntelligence = Simulation::GetSimulationObject()->CreateRandomNumber(1, 5);
	agentNegotiatingSkill = Simulation::GetSimulationObject()->CreateRandomNumber(1, 5);
	strcpy(agentFile, saveFile);
	char* temp = new char[20];
	itoa(agentIDNumber, temp, 10);
	strcat(agentFile, temp);
	strcat(agentFile, ".txt");
	delete temp;
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
	agentNegotiatingSkill = tempAgent.agentNegotiatingSkill;
	strcpy(agentFile, tempAgent.agentFile);
	foodConfidenceInterval = tempAgent.foodConfidenceInterval;
	productionConfidenceInterval = tempAgent.productionConfidenceInterval;
	luxuryConfidenceInterval = tempAgent.luxuryConfidenceInterval;
}

Agent::~Agent()
{
}