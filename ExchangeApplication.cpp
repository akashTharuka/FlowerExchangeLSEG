#include <iostream>
#include "ExchangeApplication.h"
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Validator.h"

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
}

std::string ExchangeApplication::generateUniqueOrderId()
{
	return "Order_" + std::to_string(++order_id_counter);
}

void ExchangeApplication::processOrdersCsvFile(std::string file_path)
{
	bool valid = true;
	std::ifstream file(file_path);
	if (!file.is_open())
	{
		std::cout << "Error opening file: " << file_path << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line); // skip header line
	while (std::getline(file, line))
	{
		std::stringstream iss(line);
		std::string token;
		// CSV format: client_order_id, instrument, side, quantity, price
		std::vector<std::string> tokens;
		while (std::getline(iss, token, ','))
		{
			tokens.push_back(token);
		}
		if (tokens.size() != 5)
		{
			std::cout << "Error parsing line: " << line << std::endl;
			continue;
		}
		std::string client_order_id = tokens[0];
		std::string instrument = tokens[1];
		int side = std::stoi(tokens[2]);
		int quantity = std::stoi(tokens[3]);
		double price = std::stod(tokens[4]);

		// validation
		std::string reason = Validator::validate(client_order_id, instrument, side, price, quantity);
		if (!reason.empty())
		{
			std::cout << "Invalid order: " << reason << std::endl;
			continue;
		}
		Order order(client_order_id, instrument, side, price, quantity);

	}
	file.close();
}