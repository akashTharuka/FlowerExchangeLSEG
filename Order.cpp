#include "Order.h"
#include <iostream>

Order::Order(const std::string& client_order_id, const std::string order_id, const std::string& instrument, int side, double price, int quantity)
{
	this->client_order_id = client_order_id;
	this->order_id = order_id;
	this->instrument = instrument;
	this->side = side;
	this->price = price;
	this->quantity = quantity;
}

