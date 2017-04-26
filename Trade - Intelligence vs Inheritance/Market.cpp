#include "Market.h"
#include "Agent.h"
#include "Simulation.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <fstream>
#include <cstring>
#include <string>

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
	ResolveFoodMarket();
	ResolveProductionMarket();
	ResolveLuxuryMarket();
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
	return netFoodSales / foodSales;
}

double Market::ShortAvgFoodPrice()
{
	double temp = 0.0;
	for (int i = 0; i < FoodPricePeriod.size(); i++)
	{
		temp += FoodPricePeriod[i];
	}
	return temp / FoodPricePeriod.size();
}

double Market::AvgProductionPrice()
{
	return netProductionSales / productionSales;
}

double Market::ShortAvgProductionPrice()
{
	double temp = 0.0;
	for (int i = 0; i < ProductionPricePeriod.size(); i++)
	{
		temp += ProductionPricePeriod[i];
	}
	return temp / ProductionPricePeriod.size();
}

double Market::AvgLuxuryPrice()
{
	return netLuxurySales / luxurySales;
}

double Market::ShortAvgLuxuryPrice()
{
	double temp = 0.0;
	for (int i = 0; i < LuxuryPricePeriod.size(); i++)
	{
		temp += LuxuryPricePeriod[i];
	}
	return temp / LuxuryPricePeriod.size();
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
	netFoodSales = 0;
	Simulation *worldObject = Simulation::GetSimulationObject();
	while (FoodBuyers.size() != 0 && FoodSellers.size() != 0 && FoodBuyers[0].buyPrice >= FoodSellers[0].sellPrice)
	{
		int temp;
		double price;
		int buyingAgent = FoodBuyers[0].buyingAgent;
		int sellingAgent = FoodSellers[0].sellingAgent;
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
		for (int i = 0; i < temp; i++)
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
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price)
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
			}
			else
			{
				break;
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

void Market::ResolveProductionMarket()
{
	if (ProductionPricePeriod.size() > turnsToAvg) ProductionPricePeriod.erase(ProductionPricePeriod.begin());
	netProductionSalesPeriod = 0;
	netProductionSales = 0;
	Simulation *worldObject = Simulation::GetSimulationObject();
	while (ProductionBuyers.size() != 0 && ProductionSellers.size() != 0 && ProductionBuyers[0].buyPrice >= ProductionSellers[0].sellPrice)
	{
		int temp;
		double price;
		int buyingAgent = ProductionBuyers[0].buyingAgent;
		int sellingAgent = ProductionSellers[0].sellingAgent;
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
		for (int i = 0; i < temp; i++)
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
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price)
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
			}
			else
			{
				break;
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

void Market::ResolveLuxuryMarket()
{
	if (LuxuryPricePeriod.size() > turnsToAvg) LuxuryPricePeriod.erase(LuxuryPricePeriod.begin());
	netLuxurySalesPeriod = 0;
	netLuxurySales = 0;
	Simulation *worldObject = Simulation::GetSimulationObject();
	while (LuxuryBuyers.size() != 0 && LuxurySellers.size() != 0 && LuxuryBuyers[0].buyPrice >= LuxurySellers[0].sellPrice)
	{
		int temp;
		double price;
		int buyingAgent = LuxuryBuyers[0].buyingAgent;
		int sellingAgent = LuxurySellers[0].sellingAgent;
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
		for (int i = 0; i < temp; i++)
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
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price)
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
			}
			else
			{
				break;
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