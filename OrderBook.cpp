#include "OrderBook.h"
#include <iostream>



OrderBook::OrderBook(const std::string& instrument)
{
	this->instrument = instrument;
}

OrderBook::~OrderBook()
{
	std::cout << "OrderBook destructor called" << std::endl;
}

void OrderBook::addBuyOrder(Order order)
{

}

void OrderBook::addSellOrder(Order order)
{

}
