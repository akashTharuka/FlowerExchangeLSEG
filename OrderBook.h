#pragma once
#include <string>
#include <vector>
#include "Order.h"
#include <map>
#include "ExecutionReport.h"

typedef std::map< double, std::vector<Order> > vector_map;
typedef std::map< double, std::vector<Order>, std::greater<int> > vector_map_desc;

class OrderBook
{
	public:
		/*
		Exchange app maintains one order book for each Instrument(flower type).Since there are 5 types of Instruments, there will be five separate order books in our system.
		Orderbook has two sides.Buy(blue), Sell(pink)
		Initially the orderbook is empty
		The order book receives an order. (Side = Sell, Price = 55.00, Qty = 100)
		This order will go inside sell side of the order book, and an execution report with status “New” will be disseminated
		*/
		OrderBook() {};
		OrderBook(const std::string& instrument);
		~OrderBook() {};

		// methods
		void addBuyOrder(Order order);
		void addSellOrder(Order order);
	private:
		std::string instrument;
		// buy orders are sorted in descending order
		vector_map_desc buy_orders;
		vector_map sell_orders;
};

