#include "Market.h"
#include "Agent.h"
#include "Simulation.h"
#include <vector>
#include <algorithm>
#include <thread>

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
	Simulation *worldObject = Simulation::GetSimulationObject();
	while (FoodBuyers.size() != 0 && FoodSellers.size() != 0)
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
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price)
			{
				worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
				worldObject->AgentList[sellingAgent - 1].agentMoney += price;
				worldObject->AgentList[buyingAgent - 1].agentFood++;
				worldObject->AgentList[sellingAgent - 1].agentFood--;
			}
			else
			{
				break;
			}
		}
		FoodSellers.erase(FoodSellers.begin());
		FoodBuyers.erase(FoodBuyers.begin());
	}
}

void Market::ResolveProductionMarket()
{
	Simulation *worldObject = Simulation::GetSimulationObject();
	while (ProductionBuyers.size() != 0 && ProductionSellers.size() != 0)
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
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price)
			{
				worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
				worldObject->AgentList[sellingAgent - 1].agentMoney += price;
				worldObject->AgentList[buyingAgent - 1].agentProduction++;
				worldObject->AgentList[sellingAgent - 1].agentProduction--;
			}
			else
			{
				break;
			}
		}
		ProductionSellers.erase(ProductionSellers.begin());
		ProductionBuyers.erase(ProductionBuyers.begin());
	}
}

void Market::ResolveLuxuryMarket()
{
	Simulation *worldObject = Simulation::GetSimulationObject();
	while (LuxuryBuyers.size() != 0 && LuxurySellers.size() != 0)
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
			if (worldObject->AgentList[buyingAgent - 1].agentMoney > price)
			{
				worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
				worldObject->AgentList[sellingAgent - 1].agentMoney += price;
				worldObject->AgentList[buyingAgent - 1].agentLuxury++;
				worldObject->AgentList[sellingAgent - 1].agentLuxury--;
			}
			else
			{
				break;
			}
		}
		LuxurySellers.erase(LuxurySellers.begin());
		LuxuryBuyers.erase(LuxuryBuyers.begin());
	}
}

Market::Market()
{
	FoodBuyers.resize(0);
	FoodSellers.resize(0);
	ProductionBuyers.resize(0);
	ProductionSellers.resize(0);
	LuxuryBuyers.resize(0);
	LuxurySellers.resize(0);
	netFoodSales = 0.0;
	netProudctionSales = 0.0;
	netLuxurySales = 0.0;
	foodSales = 0.0;
	productionSales = 0.0;
	luxurySales = 0.0;
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
