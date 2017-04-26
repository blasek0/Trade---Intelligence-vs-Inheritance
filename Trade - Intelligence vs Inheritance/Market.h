#pragma once
#include <vector>
#include <stdlib.h>

class Market
{
	//public variables
public:
	double netFoodSales;
	double netProductionSales;
	double netLuxurySales;
	double netFoodSalesPeriod;
	double netProductionSalesPeriod;
	double netLuxurySalesPeriod;
	double foodSalesPeriod;
	double productionSalesPeriod;
	double luxurySalesPeriod;
	double foodSales;
	double productionSales;
	double luxurySales;
	std::vector<double> FoodPricePeriod;
	std::vector<double> ProductionPricePeriod;
	std::vector<double> LuxuryPricePeriod;

	struct FoodBid
	{
		int buyingAgent;
		double buyPrice;
		int buyQuantity;
		bool operator<(const FoodBid &a) const
		{
			return buyPrice < a.buyPrice;
		}
		bool operator>(const FoodBid &a) const
		{
			return buyPrice > a.buyPrice;
		}
		bool price_sort_descending(const FoodBid &a, const FoodBid &b)
		{
			return a.buyPrice > b.buyPrice;
		}
	};
	struct FoodAsk
	{
		int sellingAgent;
		double sellPrice;
		int sellQuantity;
		bool operator<(const FoodAsk &a) const
		{
			return sellPrice < a.sellPrice;
		}
		bool operator>(const FoodAsk &a) const
		{
			return sellPrice > a.sellPrice;
		}
		bool price_sort_descending(const FoodAsk &a, const FoodAsk &b)
		{
			return a.sellPrice > b.sellPrice;
		}
	};
	struct ProductionBid
	{
		int buyingAgent;
		double buyPrice;
		int buyQuantity;
		bool operator<(const ProductionBid &a) const
		{
			return buyPrice < a.buyPrice;
		}
		bool operator>(const ProductionBid &a) const
		{
			return buyPrice > a.buyPrice;
		}
		bool price_sort_descending(const ProductionBid &a, const ProductionBid &b)
		{
			return a.buyPrice > b.buyPrice;
		}
	};
	struct ProductionAsk
	{
		int sellingAgent;
		double sellPrice;
		int sellQuantity;
		bool operator<(const ProductionAsk &a) const
		{
			return sellPrice < a.sellPrice;
		}
		bool operator>(const ProductionAsk &a) const
		{
			return sellPrice > a.sellPrice;
		}
		bool price_sort_descending(const ProductionAsk &a, const ProductionAsk &b)
		{
			return a.sellPrice > b.sellPrice;
		}
	};
	struct LuxuryBid
	{
		int buyingAgent;
		double buyPrice;
		int buyQuantity;
		bool operator<(const LuxuryBid &a) const
		{
			return buyPrice < a.buyPrice;
		}
		bool operator>(const LuxuryBid &a) const
		{
			return buyPrice > a.buyPrice;
		}
		bool price_sort_descending(const LuxuryBid &a, const LuxuryBid &b)
		{
			return a.buyPrice > b.buyPrice;
		}
	};
	struct LuxuryAsk
	{
		int sellingAgent;
		double sellPrice;
		int sellQuantity;
		bool operator<(const LuxuryAsk &a) const
		{
			return sellPrice < a.sellPrice;
		}
		bool operator>(const LuxuryAsk &a) const
		{
			return sellPrice > a.sellPrice;
		}
		bool price_sort_descending(const LuxuryAsk &a, const LuxuryAsk &b)
		{
			return a.sellPrice > b.sellPrice;
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