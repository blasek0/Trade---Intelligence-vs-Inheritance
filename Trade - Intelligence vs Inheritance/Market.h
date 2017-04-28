#pragma once
#include <fstream>
#include <vector>
#include <stdlib.h>

class Market
{
	//public variables
public:
	int turnsToAvg;
	double netFoodSales;
	double netProductionSales;
	double netLuxurySales;
	double netFoodSalesPeriod;
	double netProductionSalesPeriod;
	double netLuxurySalesPeriod;
	int foodSalesPeriod;
	int productionSalesPeriod;
	int luxurySalesPeriod;
	int foodSales;
	int productionSales;
	int luxurySales;
	std::vector<double> FoodPricePeriod;
	std::vector<double> ProductionPricePeriod;
	std::vector<double> LuxuryPricePeriod;
	std::fstream outfile;
	char saveFile[100];

	struct FoodBid
	{
		int buyingAgent;
		double buyPrice;
		int buyQuantity;
		bool operator<(const FoodBid &a) const
		{ //Overloaded < operator allows std::sort() to work on this struct with no need for custom sorting function
			return buyPrice < a.buyPrice;
		}
	};
	struct FoodAsk
	{
		int sellingAgent;
		double sellPrice;
		int sellQuantity;
		bool operator<(const FoodAsk &a) const
		{ //Overloaded < operator allows std::sort() to work on this struct with no need for custom sorting function
			return sellPrice < a.sellPrice;
		}
	};
	struct ProductionBid
	{
		int buyingAgent;
		double buyPrice;
		int buyQuantity;
		bool operator<(const ProductionBid &a) const
		{ //Overloaded < operator allows std::sort() to work on this struct with no need for custom sorting function
			return buyPrice < a.buyPrice;
		}
	};
	struct ProductionAsk
	{
		int sellingAgent;
		double sellPrice;
		int sellQuantity;
		bool operator<(const ProductionAsk &a) const
		{ //Overloaded < operator allows std::sort() to work on this struct with no need for custom sorting function
			return sellPrice < a.sellPrice;
		}
	};
	struct LuxuryBid
	{
		int buyingAgent;
		double buyPrice;
		int buyQuantity;
		bool operator<(const LuxuryBid &a) const
		{ //Overloaded < operator allows std::sort() to work on this struct with no need for custom sorting function
			return buyPrice < a.buyPrice;
		}
	};
	struct LuxuryAsk
	{
		int sellingAgent;
		double sellPrice;
		int sellQuantity;
		bool operator<(const LuxuryAsk &a) const
		{ //Overloaded < operator allows std::sort() to work on this struct with no need for custom sorting function
			return sellPrice < a.sellPrice;
		}
	};
	std::vector<FoodAsk> FoodSellers;
	std::vector<FoodBid> FoodBuyers;
	std::vector<ProductionAsk> ProductionSellers;
	std::vector<ProductionBid> ProductionBuyers;
	std::vector<LuxuryAsk> LuxurySellers;
	std::vector<LuxuryBid> LuxuryBuyers;

	//public functions
public:
	void SortMarkets();
	void ResolveBooks();
	void CreateBid(int buyingAgent, int commodityType, double buyPrice, int max);
	void CreateAsk(int sellingAgent, int commodityType, double sellPrice, int min);
	double AvgFoodPrice();
	double ShortAvgFoodPrice();
	double AvgProductionPrice();
	double ShortAvgProductionPrice();
	double AvgLuxuryPrice();
	double ShortAvgLuxuryPrice();
	void WriteMarketState();

private:
	void CreateFoodBid(int buyingAgent, double buyPrice, int max);
	void CreateProductionBid(int buyingAgent, double buyPrice, int max);
	void CreateLuxuryBid(int buyingAgent, double buyPrice, int max);
	void CreateFoodAsk(int sellingAgent, double sellPrice, int min);
	void CreateProductionAsk(int sellingAgent, double sellPrice, int min);
	void CreateLuxuryAsk(int sellingAgent, double sellPrice, int min);
	void ResolveFoodMarket();
	void ResolveProductionMarket();
	void ResolveLuxuryMarket();

	//constructors & destructors
public:
	Market();
	~Market();
};