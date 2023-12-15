#pragma once
#include <string>
#include <vector>
#include "Order.h"

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
		OrderBook(const std::string& instrument, std::vector<Order> buy_orders, std::vector<Order> sell_orders);
		~OrderBook();

		// Getters
		std::string getInstrument() const { return instrument; }
		std::vector<Order> getBuyOrders() const { return buy_orders; }
		std::vector<Order> getSellOrders() const { return sell_orders; }

		// methods
		void addBuyOrder(Order order);
		void addSellOrder(Order order);
	private:
		std::string instrument;
		std::vector<Order> buy_orders;
		std::vector<Order> sell_orders;

};

