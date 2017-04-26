#include "Market.h"
#include "Agent.h"
#include "Simulation.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Simulation;
Agent;

void Market::SortMarkets()
{
	std::random_shuffle(FoodBuyers.begin(), FoodBuyers.end());
	std::random_shuffle(FoodSellers.begin(), FoodSellers.end());
	std::random_shuffle(ProductionBuyers.begin(), ProductionBuyers.end());
	std::random_shuffle(ProductionSellers.begin(), ProductionSellers.end());
	std::random_shuffle(LuxuryBuyers.begin(), LuxuryBuyers.end());
	std::random_shuffle(LuxurySellers.begin(), LuxurySellers.end());
	std::sort(FoodBuyers.begin(), FoodBuyers.end());
	std::reverse(FoodBuyers.begin(), FoodBuyers.end());
	std::sort(FoodSellers.begin(), FoodSellers.end());
	std::sort(ProductionBuyers.begin(), ProductionBuyers.end());
	std::reverse(ProductionBuyers.begin(), ProductionBuyers.end());
	std::sort(ProductionSellers.begin(), ProductionSellers.end());
	std::sort(LuxuryBuyers.begin(), LuxuryBuyers.end());
	std::reverse(LuxuryBuyers.begin(), LuxuryBuyers.end());
	std::sort(LuxurySellers.begin(), LuxurySellers.end());
}

void Market::ResolveBooks()
{
	cout << "Starting food market.\n";
	ResolveFoodMarket();
	cout << "Starting production market.\n";
	//ResolveProductionMarket();
	cout << "Starting luxury market.\n";
	//ResolveLuxuryMarket();
	cout << "Finished luxury market.\n";
}

void Market::CreateBid(int buyingAgent, int commodityType, double buyPrice, int max)
{
	switch (commodityType)
	{
	case 1:
		CreateFoodBid(buyingAgent, buyPrice, max);
		break;
	case 2:
		CreateProductionBid(buyingAgent, buyPrice, max);
		break;
	case 3:
		CreateLuxuryBid(buyingAgent, buyPrice, max);
		break;
	default:
		return;
	}
}

void Market::CreateAsk(int sellingAgent, int commodityType, double sellPrice, int min)
{
	switch (commodityType)
	{
	case 1:
		CreateFoodAsk(sellingAgent, sellPrice, min);
		break;
	case 2:
		CreateProductionAsk(sellingAgent, sellPrice, min);
		break;
	case 3:
		CreateLuxuryAsk(sellingAgent, sellPrice, min);
		break;
	default:
		return;
	}
}

double Market::AvgFoodPrice()
{
	if (foodSales == 0)
	{
		return 1.0;
	}
	else
	{
		return netFoodSales / foodSales;
	}
}

double Market::ShortAvgFoodPrice()
{
	if (FoodPricePeriod.size() == 0)
	{
		double temp = 0.0;
		for (int i = 0; i < FoodPricePeriod.size(); i++)
		{
			temp += FoodPricePeriod[i];
		}
		temp = temp / FoodPricePeriod.size();
		if (temp > 0)
		{
			return temp;
		}
		else
		{
			return 1.0;
		}
	}
	else
	{
		return 1.0;
	}
}

double Market::AvgProductionPrice()
{
	if (productionSales == 0)
	{
		return 1.0;
	}
	else
	{
		return netProductionSales / productionSales;
	}
}

double Market::ShortAvgProductionPrice()
{
	if (ProductionPricePeriod.size() == 0)
	{
		double temp = 0.0;
		for (int i = 0; i < ProductionPricePeriod.size(); i++)
		{
			temp += ProductionPricePeriod[i];
		}
		temp = temp / ProductionPricePeriod.size();
		if (temp > 0)
		{
			return temp;
		}
		else
		{
			return 1.0;
		}
	}
	else
	{
		return 1.0;
	}
}

double Market::AvgLuxuryPrice()
{
	if (luxurySales == 0)
	{
		return 1.0;
	}
	else
	{
		return netLuxurySales / luxurySales;
	}
}

double Market::ShortAvgLuxuryPrice()
{
	if (LuxuryPricePeriod.size() == 0)
	{
		double temp = 0.0;
		for (int i = 0; i < LuxuryPricePeriod.size(); i++)
		{
			temp += LuxuryPricePeriod[i];
		}
		temp = temp / LuxuryPricePeriod.size();
		if (temp > 0)
		{
			return temp;
		}
		else
		{
			return 1.0;
		}
	}
	else
	{
		return 1.0;
	}
}

void Market::WriteMarketState()
{
	if (!outfile.is_open())
	{
		outfile.open(saveFile, ios::app);
	}
	char* temp = new char[255];
	strcpy(temp, std::to_string(AvgFoodPrice()).c_str()); //Total$
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(foodSales, temp, 10); //Total#
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	strcpy(temp, std::to_string(ShortAvgFoodPrice()).c_str());//Short-term$
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	strcpy(temp, std::to_string(AvgProductionPrice()).c_str()); //Total$
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(productionSales, temp, 10); //Total#
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	strcpy(temp, std::to_string(ShortAvgProductionPrice()).c_str());//Short-term$
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	strcpy(temp, std::to_string(AvgLuxuryPrice()).c_str()); //Total$
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(luxurySales, temp, 10); //Total#
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	strcpy(temp, std::to_string(ShortAvgLuxuryPrice()).c_str());//Short-term$
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	strcpy(temp, "");
	itoa(Simulation::GetSimulationObject()->turnNumber, temp, 10);
	strcat(temp, ", ");
	outfile.write(temp, strlen(temp));
	outfile.write("\n", 1);
	delete temp;
}

void Market::CreateFoodBid(int buyingAgent, double buyPrice, int max)
{
	FoodBid *bid = new FoodBid();
	bid->buyingAgent = buyingAgent;
	bid->buyPrice = buyPrice;
	bid->buyQuantity = max;
	FoodBuyers.push_back(*bid);
}

void Market::CreateProductionBid(int buyingAgent, double buyPrice, int max)
{
	ProductionBid *bid = new ProductionBid();
	bid->buyingAgent = buyingAgent;
	bid->buyPrice = buyPrice;
	bid->buyQuantity = max;
	ProductionBuyers.push_back(*bid);
}

void Market::CreateLuxuryBid(int buyingAgent, double buyPrice, int max)
{
	LuxuryBid *bid = new LuxuryBid();
	bid->buyingAgent = buyingAgent;
	bid->buyPrice = buyPrice;
	bid->buyQuantity = max;
	LuxuryBuyers.push_back(*bid);
}

void Market::CreateFoodAsk(int sellingAgent, double sellPrice, int min)
{
	FoodAsk *bid = new FoodAsk();
	bid->sellingAgent = sellingAgent;
	bid->sellPrice = sellPrice;
	bid->sellQuantity = min;
	FoodSellers.push_back(*bid);
}

void Market::CreateProductionAsk(int sellingAgent, double sellPrice, int min)
{
	ProductionAsk *bid = new ProductionAsk();
	bid->sellingAgent = sellingAgent;
	bid->sellPrice = sellPrice;
	bid->sellQuantity = min;
	ProductionSellers.push_back(*bid);
}

void Market::CreateLuxuryAsk(int sellingAgent, double sellPrice, int min)
{
	LuxuryAsk *bid = new LuxuryAsk();
	bid->sellingAgent = sellingAgent;
	bid->sellPrice = sellPrice;
	bid->sellQuantity = min;
	LuxurySellers.push_back(*bid);
}

void Market::ResolveFoodMarket()
{
	if (FoodPricePeriod.size() > turnsToAvg) FoodPricePeriod.erase(FoodPricePeriod.begin());
	netFoodSalesPeriod = 0;
	foodSalesPeriod;
	Simulation *worldObject = Simulation::GetSimulationObject();
	cout << FoodBuyers.size() << "Food buyers. " << FoodSellers.size() << "Food sellers.\n";
	int temp;
	double price;
	int buyingAgent;
	int sellingAgent;

	while (FoodBuyers.size() != 0 && FoodSellers.size() != 0 && FoodBuyers[0].buyPrice >= FoodSellers[0].sellPrice)
	{
		buyingAgent = FoodBuyers[0].buyingAgent;
		sellingAgent = FoodSellers[0].sellingAgent;
		if (FoodBuyers[0].buyQuantity > FoodSellers[0].sellQuantity)
		{
			temp = FoodSellers[0].sellQuantity;
		}
		else
		{
			temp = FoodBuyers[0].buyQuantity;
		}
		price = worldObject->GetPrice(FoodBuyers[0].buyPrice, FoodSellers[0].sellPrice,
			buyingAgent, sellingAgent);
		for (int i = 0; i < temp+1; i++)
		{
			if (FoodBuyers[0].buyQuantity == 0)
			{
				FoodBuyers.erase(FoodBuyers.begin());
				break;
			}
			if (FoodSellers[0].sellQuantity == 0)
			{
				FoodSellers.erase(FoodSellers.begin());
				break;
			}
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price && worldObject->AgentList[sellingAgent - 1].agentFood > 0)
			{
				worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
				worldObject->AgentList[sellingAgent - 1].agentMoney += price;
				worldObject->AgentList[buyingAgent - 1].agentFood++;
				worldObject->AgentList[sellingAgent - 1].agentFood--;
				netFoodSales += price;
				netFoodSalesPeriod += price;
				foodSales++;
				foodSalesPeriod++;
				FoodBuyers[0].buyQuantity--;
				FoodSellers[0].sellQuantity--;
				cout << "Sale processed\n";
				worldObject->AgentList[buyingAgent - 1].SuccessfulFoodBid(price);
				worldObject->AgentList[sellingAgent - 1].SuccessfulFoodBid(price);
			}
		}
	}
	while (FoodBuyers.size() != 0)
	{
		worldObject->AgentList[(FoodBuyers[0].buyingAgent - 1)].FailedFoodBid(FoodBuyers[0].buyPrice);
		FoodBuyers.erase(FoodBuyers.begin());
	}
	while (FoodSellers.size() != 0)
	{
		worldObject->AgentList[(FoodSellers[0].sellingAgent - 1)].FailedFoodBid(FoodSellers[0].sellPrice);
		FoodSellers.erase(FoodSellers.begin());
	}
	FoodPricePeriod.push_back(netFoodSalesPeriod / foodSalesPeriod);
}

void Market::ResolveProductionMarket() {
	if (ProductionPricePeriod.size() > turnsToAvg) ProductionPricePeriod.erase(ProductionPricePeriod.begin());
	netProductionSalesPeriod = 0;
	productionSalesPeriod;
	Simulation *worldObject = Simulation::GetSimulationObject();
	cout << ProductionBuyers.size() << "Production buyers. " << ProductionSellers.size() << "Production sellers.\n";
	int temp;
	double price;
	int buyingAgent;
	int sellingAgent;

	while (ProductionBuyers.size() != 0 && ProductionSellers.size() != 0 && ProductionBuyers[0].buyPrice >= ProductionSellers[0].sellPrice)
	{
		buyingAgent = ProductionBuyers[0].buyingAgent;
		sellingAgent = ProductionSellers[0].sellingAgent;
		if (ProductionBuyers[0].buyQuantity > ProductionSellers[0].sellQuantity)
		{
			temp = ProductionSellers[0].sellQuantity;
		}
		else
		{
			temp = ProductionBuyers[0].buyQuantity;
		}
		price = worldObject->GetPrice(ProductionBuyers[0].buyPrice, ProductionSellers[0].sellPrice,
			buyingAgent, sellingAgent);
		for (int i = 0; i < temp + 1; i++)
		{
			if (ProductionBuyers[0].buyQuantity == 0)
			{
				ProductionBuyers.erase(ProductionBuyers.begin());
				break;
			}
			if (ProductionSellers[0].sellQuantity == 0)
			{
				ProductionSellers.erase(ProductionSellers.begin());
				break;
			}
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price && worldObject->AgentList[sellingAgent - 1].agentProduction > 0)
			{
				worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
				worldObject->AgentList[sellingAgent - 1].agentMoney += price;
				worldObject->AgentList[buyingAgent - 1].agentProduction++;
				worldObject->AgentList[sellingAgent - 1].agentProduction--;
				netProductionSales += price;
				netProductionSalesPeriod += price;
				productionSales++;
				productionSalesPeriod++;
				ProductionBuyers[0].buyQuantity--;
				ProductionSellers[0].sellQuantity--;
				cout << "Sale processed\n";
				worldObject->AgentList[buyingAgent - 1].SuccessfulProductionBid(price);
				worldObject->AgentList[sellingAgent - 1].SuccessfulProductionBid(price);
			}
		}
	}
	while (ProductionBuyers.size() != 0)
	{
		worldObject->AgentList[(ProductionBuyers[0].buyingAgent - 1)].FailedProductionBid(ProductionBuyers[0].buyPrice);
		ProductionBuyers.erase(ProductionBuyers.begin());
	}
	while (ProductionSellers.size() != 0)
	{
		worldObject->AgentList[(ProductionSellers[0].sellingAgent - 1)].FailedProductionBid(ProductionSellers[0].sellPrice);
		ProductionSellers.erase(ProductionSellers.begin());
	}
	ProductionPricePeriod.push_back(netProductionSalesPeriod / productionSalesPeriod);
}

void Market::ResolveLuxuryMarket() {
	if (LuxuryPricePeriod.size() > turnsToAvg) LuxuryPricePeriod.erase(LuxuryPricePeriod.begin());
	netLuxurySalesPeriod = 0;
	luxurySalesPeriod;
	Simulation *worldObject = Simulation::GetSimulationObject();
	cout << LuxuryBuyers.size() << "Luxury buyers. " << LuxurySellers.size() << "Luxury sellers.\n";
	int temp;
	double price;
	int buyingAgent;
	int sellingAgent;

	while (LuxuryBuyers.size() != 0 && LuxurySellers.size() != 0 && LuxuryBuyers[0].buyPrice >= LuxurySellers[0].sellPrice)
	{
		buyingAgent = LuxuryBuyers[0].buyingAgent;
		sellingAgent = LuxurySellers[0].sellingAgent;
		if (LuxuryBuyers[0].buyQuantity > LuxurySellers[0].sellQuantity)
		{
			temp = LuxurySellers[0].sellQuantity;
		}
		else
		{
			temp = LuxuryBuyers[0].buyQuantity;
		}
		price = worldObject->GetPrice(LuxuryBuyers[0].buyPrice, LuxurySellers[0].sellPrice,
			buyingAgent, sellingAgent);
		for (int i = 0; i < temp + 1; i++)
		{
			if (LuxuryBuyers[0].buyQuantity == 0)
			{
				LuxuryBuyers.erase(LuxuryBuyers.begin());
				break;
			}
			if (LuxurySellers[0].sellQuantity == 0)
			{
				LuxurySellers.erase(LuxurySellers.begin());
				break;
			}
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price && worldObject->AgentList[sellingAgent - 1].agentLuxury > 0)
			{
				worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
				worldObject->AgentList[sellingAgent - 1].agentMoney += price;
				worldObject->AgentList[buyingAgent - 1].agentLuxury++;
				worldObject->AgentList[sellingAgent - 1].agentLuxury--;
				netLuxurySales += price;
				netLuxurySalesPeriod += price;
				luxurySales++;
				luxurySalesPeriod++;
				LuxuryBuyers[0].buyQuantity--;
				LuxurySellers[0].sellQuantity--;
				cout << "Sale processed\n";
				worldObject->AgentList[buyingAgent - 1].SuccessfulLuxuryBid(price);
				worldObject->AgentList[sellingAgent - 1].SuccessfulLuxuryBid(price);
			}
		}
	}
	while (LuxuryBuyers.size() != 0)
	{
		worldObject->AgentList[(LuxuryBuyers[0].buyingAgent - 1)].FailedLuxuryBid(LuxuryBuyers[0].buyPrice);
		LuxuryBuyers.erase(LuxuryBuyers.begin());
	}
	while (LuxurySellers.size() != 0)
	{
		worldObject->AgentList[(LuxurySellers[0].sellingAgent - 1)].FailedLuxuryBid(LuxurySellers[0].sellPrice);
		LuxurySellers.erase(LuxurySellers.begin());
	}
	LuxuryPricePeriod.push_back(netLuxurySalesPeriod / luxurySalesPeriod);
}

Market::Market()
{
	FoodBuyers.resize(0);
	FoodSellers.resize(0);
	ProductionBuyers.resize(0);
	ProductionSellers.resize(0);
	LuxuryBuyers.resize(0);
	LuxurySellers.resize(0);
	FoodPricePeriod.resize(0);
	ProductionPricePeriod.resize(0);
	LuxuryPricePeriod.resize(0);
	turnsToAvg = 0;
	netFoodSales = 0.0;
	netProductionSales = 0.0;
	netLuxurySales = 0.0;
	netFoodSalesPeriod = 0.0;
	netProductionSalesPeriod = 0.0;
	netLuxurySalesPeriod = 0.0;
	foodSalesPeriod = 0.0;
	productionSalesPeriod = 0.0;
	luxurySalesPeriod = 0.0;
	foodSales = 0.0;
	productionSales = 0.0;
	luxurySales = 0.0;
	strcpy(saveFile, "Market.txt");
	if (!outfile.is_open())
	{
		outfile.open(saveFile, ios::out, ios::trunc);
	}
	char* temp = new char[255];
	strcpy(temp, "Avg. Food Price, # sales, short term avg, Avg. Production Price, # sales, short term avg, Avg. Luxury Price, # sales, short term avg, Turn Number, ");
	outfile.write(temp, strlen(temp));
	outfile.write("\n", 1);
	outfile.close();
	delete temp;
}


Market::~Market()
{
	FoodBuyers.clear();
	FoodSellers.clear();
	ProductionBuyers.clear();
	ProductionSellers.clear();
	LuxuryBuyers.clear();
	LuxurySellers.clear();
}