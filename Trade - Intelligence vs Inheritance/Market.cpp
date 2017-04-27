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
	if (FoodPricePeriod.size() != 0)
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
	if (ProductionPricePeriod.size() != 0)
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
	if (LuxuryPricePeriod.size() != 0)
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
	if (FoodPricePeriod.size() > turnsToAvg)
	{
		//cout << "Erasing first foodPrice\n";
		FoodPricePeriod.erase(FoodPricePeriod.begin());
	}
	int buyingIndex = 0;
	int sellingIndex = 0;
	netFoodSalesPeriod = 0;
	foodSalesPeriod;
	Simulation *worldObject = Simulation::GetSimulationObject();
	int temp;
	double price;
	int buyingAgent;
	int sellingAgent;
	//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	while (!FoodBuyers.empty() && !FoodSellers.empty())
	{
		buyingAgent = FoodBuyers.front().buyingAgent;
		sellingAgent = FoodSellers.front().sellingAgent;
		price = worldObject->GetPrice(FoodBuyers.front().buyPrice, FoodSellers.front().sellPrice,
			buyingAgent, sellingAgent);
		if (FoodBuyers.front().buyQuantity > FoodSellers.front().sellQuantity)
		{
			temp = FoodSellers.front().sellQuantity;
		}
		else
		{
			temp = FoodBuyers.front().buyQuantity;
		}
		if (worldObject->AgentList[buyingAgent - 1].agentMoney > price 
			&& worldObject->AgentList[sellingAgent - 1].agentFood > 0
				&& FoodBuyers.front().buyPrice >= FoodSellers.front().sellPrice
					&& FoodBuyers.front().buyQuantity > 0 
						&& FoodSellers.front().sellQuantity > 0)
		{
			worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
			worldObject->AgentList[sellingAgent - 1].agentMoney += price;
			worldObject->AgentList[buyingAgent - 1].agentFood++;
			worldObject->AgentList[sellingAgent - 1].agentFood--;
			netFoodSales += price;
			netFoodSalesPeriod += price;
			foodSales++;
			foodSalesPeriod++;
			FoodBuyers.front().buyQuantity--;
			FoodSellers.front().sellQuantity--;
			//cout << "Sale processed\n";
			worldObject->AgentList[buyingAgent - 1].SuccessfulFoodBid(price);
			worldObject->AgentList[sellingAgent - 1].SuccessfulFoodBid(price);
		}
		if (!FoodSellers.empty() && !FoodBuyers.empty())
		{
			if (FoodSellers.front().sellPrice > FoodBuyers.front().buyPrice)
			{
				//cout << "Sell price > buy price, break\n";
				break;
			}
		}
		while (!FoodBuyers.empty() && FoodBuyers.front().buyQuantity <= 0)
		{
			//cout << "BuyQuantity = 0\n";
			buyingIndex++;
			FoodBuyers.erase(FoodBuyers.begin());
		}
		while (!FoodSellers.empty() && FoodSellers.front().sellQuantity <= 0)
		{
			//cout << "SellQuantity = 0\n";
			sellingIndex++;
			FoodSellers.erase(FoodSellers.begin());
		}
		if (FoodBuyers.empty() || FoodSellers.empty())
		{
			//cout << "Buy or Sell list is empty, break\n";
			break;
		}
		if (worldObject->AgentList[buyingAgent - 1].agentMoney < price)
		{
			FoodBuyers.erase(FoodBuyers.begin());
		}
		if (worldObject->AgentList[FoodSellers.front().sellingAgent - 1].agentFood < 0)
		{
			FoodSellers.erase(FoodSellers.begin());
		}
	}
	//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	while (!FoodBuyers.empty())
	{
		worldObject->AgentList[(FoodBuyers.front().buyingAgent - 1)].FailedFoodBid(FoodBuyers.front().buyPrice);
		FoodBuyers.erase(FoodBuyers.begin());
	}
	while (!FoodSellers.empty())
	{
		worldObject->AgentList[(FoodSellers.front().sellingAgent - 1)].FailedFoodBid(FoodSellers.front().sellPrice);
		FoodSellers.erase(FoodSellers.begin());
	}
	FoodPricePeriod.push_back(netFoodSalesPeriod / foodSalesPeriod);
}

void Market::ResolveProductionMarket()
{
	if (ProductionPricePeriod.size() > turnsToAvg)
	{
		//cout << "Erasing first productionPrice\n";
		ProductionPricePeriod.erase(ProductionPricePeriod.begin());
	}
	int buyingIndex = 0;
	int sellingIndex = 0;
	netProductionSalesPeriod = 0;
	productionSalesPeriod;
	Simulation *worldObject = Simulation::GetSimulationObject();
	int temp;
	double price;
	int buyingAgent;
	int sellingAgent;
	//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	while (!ProductionBuyers.empty() && !ProductionSellers.empty())
	{
		buyingAgent = ProductionBuyers.front().buyingAgent;
		sellingAgent = ProductionSellers.front().sellingAgent;
		price = worldObject->GetPrice(ProductionBuyers.front().buyPrice, ProductionSellers.front().sellPrice,
			buyingAgent, sellingAgent);
		if (ProductionBuyers.front().buyQuantity > ProductionSellers.front().sellQuantity)
		{
			temp = ProductionSellers.front().sellQuantity;
		}
		else
		{
			temp = ProductionBuyers.front().buyQuantity;
		}
		if (worldObject->AgentList[buyingAgent - 1].agentMoney > price
			&& worldObject->AgentList[sellingAgent - 1].agentProduction > 0
			&& ProductionBuyers.front().buyPrice >= ProductionSellers.front().sellPrice
			&& ProductionBuyers.front().buyQuantity > 0
			&& ProductionSellers.front().sellQuantity > 0)
		{
			worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
			worldObject->AgentList[sellingAgent - 1].agentMoney += price;
			worldObject->AgentList[buyingAgent - 1].agentProduction++;
			worldObject->AgentList[sellingAgent - 1].agentProduction--;
			netProductionSales += price;
			netProductionSalesPeriod += price;
			productionSales++;
			productionSalesPeriod++;
			ProductionBuyers.front().buyQuantity--;
			ProductionSellers.front().sellQuantity--;
			//cout << "Sale processed\n";
			worldObject->AgentList[buyingAgent - 1].SuccessfulProductionBid(price);
			worldObject->AgentList[sellingAgent - 1].SuccessfulProductionBid(price);
		}
		if (!ProductionSellers.empty() && !ProductionBuyers.empty())
		{
			if (ProductionSellers.front().sellPrice > ProductionBuyers.front().buyPrice)
			{
				//cout << "Sell price > buy price, break\n";
				break;
			}
		}
		while (!ProductionBuyers.empty() && ProductionBuyers.front().buyQuantity <= 0)
		{
			//cout << "BuyQuantity = 0\n";
			buyingIndex++;
			ProductionBuyers.erase(ProductionBuyers.begin());
		}
		while (!ProductionSellers.empty() && ProductionSellers.front().sellQuantity <= 0)
		{
			//cout << "SellQuantity = 0\n";
			sellingIndex++;
			ProductionSellers.erase(ProductionSellers.begin());
		}
		if (ProductionBuyers.empty() || ProductionSellers.empty())
		{
			//cout << "Buy or Sell list is empty, break\n";
			break;
		}
		if (worldObject->AgentList[buyingAgent - 1].agentMoney < price)
		{
			ProductionBuyers.erase(ProductionBuyers.begin());
		}
		if (worldObject->AgentList[ProductionSellers.front().sellingAgent - 1].agentProduction < 0)
		{
			ProductionSellers.erase(ProductionSellers.begin());
		}
	}
	//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	while (!ProductionBuyers.empty())
	{
		worldObject->AgentList[(ProductionBuyers.front().buyingAgent - 1)].FailedProductionBid(ProductionBuyers.front().buyPrice);
		ProductionBuyers.erase(ProductionBuyers.begin());
	}
	while (!ProductionSellers.empty())
	{
		worldObject->AgentList[(ProductionSellers.front().sellingAgent - 1)].FailedProductionBid(ProductionSellers.front().sellPrice);
		ProductionSellers.erase(ProductionSellers.begin());
	}
	ProductionPricePeriod.push_back(netProductionSalesPeriod / foodSalesPeriod);
}

void Market::ResolveLuxuryMarket()
{
	if (LuxuryPricePeriod.size() > turnsToAvg)
	{
		//cout << "Erasing first luxuryPrice\n";
		LuxuryPricePeriod.erase(LuxuryPricePeriod.begin());
	}
	int buyingIndex = 0;
	int sellingIndex = 0;
	netLuxurySalesPeriod = 0;
	luxurySalesPeriod;
	Simulation *worldObject = Simulation::GetSimulationObject();
	int temp;
	double price;
	int buyingAgent;
	int sellingAgent;
	//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	while (!LuxuryBuyers.empty() && !LuxurySellers.empty())
	{
		buyingAgent = LuxuryBuyers.front().buyingAgent;
		sellingAgent = LuxurySellers.front().sellingAgent;
		price = worldObject->GetPrice(LuxuryBuyers.front().buyPrice, LuxurySellers.front().sellPrice,
			buyingAgent, sellingAgent);
		if (LuxuryBuyers.front().buyQuantity > LuxurySellers.front().sellQuantity)
		{
			temp = LuxurySellers.front().sellQuantity;
		}
		else
		{
			temp = LuxuryBuyers.front().buyQuantity;
		}
		if (worldObject->AgentList[buyingAgent - 1].agentMoney > price
			&& worldObject->AgentList[sellingAgent - 1].agentLuxury > 0
			&& LuxuryBuyers.front().buyPrice >= LuxurySellers.front().sellPrice
			&& LuxuryBuyers.front().buyQuantity > 0
			&& LuxurySellers.front().sellQuantity > 0)
		{
			worldObject->AgentList[buyingAgent - 1].agentMoney -= price;
			worldObject->AgentList[sellingAgent - 1].agentMoney += price;
			worldObject->AgentList[buyingAgent - 1].agentLuxury++;
			worldObject->AgentList[sellingAgent - 1].agentLuxury--;
			netLuxurySales += price;
			netLuxurySalesPeriod += price;
			luxurySales++;
			luxurySalesPeriod++;
			LuxuryBuyers.front().buyQuantity--;
			LuxurySellers.front().sellQuantity--;
			//cout << "Sale processed\n";
			worldObject->AgentList[buyingAgent - 1].SuccessfulLuxuryBid(price);
			worldObject->AgentList[sellingAgent - 1].SuccessfulLuxuryBid(price);
		}
		if (!LuxurySellers.empty() && !LuxuryBuyers.empty())
		{
			if (LuxurySellers.front().sellPrice > LuxuryBuyers.front().buyPrice)
			{
				//cout << "Sell price > buy price, break\n";
				break;
			}
		}
		while (!LuxuryBuyers.empty() && LuxuryBuyers.front().buyQuantity <= 0)
		{
			//cout << "BuyQuantity = 0\n";
			buyingIndex++;
			LuxuryBuyers.erase(LuxuryBuyers.begin());
		}
		while (!LuxurySellers.empty() && LuxurySellers.front().sellQuantity <= 0)
		{
			//cout << "SellQuantity = 0\n";
			sellingIndex++;
			LuxurySellers.erase(LuxurySellers.begin());
		}
		if (LuxuryBuyers.empty() || LuxurySellers.empty())
		{
			//cout << "Buy or Sell list is empty, break\n";
			break;
		}
		if (worldObject->AgentList[buyingAgent - 1].agentMoney < price)
		{
			LuxuryBuyers.erase(LuxuryBuyers.begin());
		}
		if (worldObject->AgentList[LuxurySellers.front().sellingAgent - 1].agentLuxury < 0)
		{
			LuxurySellers.erase(LuxurySellers.begin());
		}
	}
	//cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	while (!LuxuryBuyers.empty())
	{
		worldObject->AgentList[(LuxuryBuyers.front().buyingAgent - 1)].FailedLuxuryBid(LuxuryBuyers.front().buyPrice);
		LuxuryBuyers.erase(LuxuryBuyers.begin());
	}
	while (!LuxurySellers.empty())
	{
		worldObject->AgentList[(LuxurySellers.front().sellingAgent - 1)].FailedLuxuryBid(LuxurySellers.front().sellPrice);
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