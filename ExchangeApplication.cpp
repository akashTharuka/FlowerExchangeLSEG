#include <iostream>
#include "ExchangeApplication.h"
#include <fstream>
#include <sstream>
#include "Utils.h"

int ExchangeApplication::order_id_counter = 0;

ExchangeApplication::ExchangeApplication()
{
	order_books[InstrumentType::Rose] = OrderBook("Rose");
	order_books[InstrumentType::Lavender] = OrderBook("Lavender");
	order_books[InstrumentType::Lotus] = OrderBook("Lotus");
	order_books[InstrumentType::Tulip] = OrderBook("Tulip");
	order_books[InstrumentType::Orchid] = OrderBook("Orchid");
}

ExchangeApplication::~ExchangeApplication()
{
	std::cout << "ExchangeApplication destructor called" << std::endl;
}

std::string ExchangeApplication::generateUniqueOrderId()
{
	return "Order_" + std::to_string(++order_id_counter);
}

void ExchangeApplication::processOrdersCsvFile(std::string file_path)
{
	
}