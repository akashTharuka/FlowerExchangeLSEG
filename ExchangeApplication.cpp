#include <iostream>
#include "ExchangeApplication.h"
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Validator.h"
#include "Enums.h"

std::vector<ExecutionReport> ExchangeApplication::execution_reports;

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
	static int order_id_counter = 0;
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
			std::string order_id = generateUniqueOrderId();
			int exec_status = ExecutionStatus::Rejected;
			std::string transaction_time = FlowerExchangeUtils::formatTransactionTime();
			ExecutionReport exec_rep = ExecutionReport(client_order_id, order_id, instrument, side, price, quantity, exec_status, transaction_time, reason);
			addExecutionReport(exec_rep);
			continue;
		}
		Order order(client_order_id, instrument, side, price, quantity);
		OrderBook& order_book = (instrument == "Rose") ? order_books[InstrumentType::Rose] :
			(instrument == "Lavender") ? order_books[InstrumentType::Lavender] :
			(instrument == "Lotus") ? order_books[InstrumentType::Lotus] :
			(instrument == "Tulip") ? order_books[InstrumentType::Tulip] :
			order_books[InstrumentType::Orchid];

		if (side == 1)
		{
			order_book.addBuyOrder(order, generateUniqueOrderId());
			std::cout << "Buy order added: " << line << std::endl;
		}
		else if (side == 2)
		{
			order_book.addSellOrder(order, generateUniqueOrderId());
			std::cout << "Sell order added: " << line << std::endl;
		}

	}
	file.close();
}

void ExchangeApplication::writeToCsvFile(std::vector<ExecutionReport> execution_reports, std::string file_path)
{
	std::ofstream file(file_path);

	if (!file.is_open()) 
	{
		std::cerr << "Error opening file: " << file_path << std::endl;
		return;
	}

	// Write header
	file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price\n";

	std::cout << execution_reports.size() << std::endl;

	// Write orders
	for (const auto& exec_rep : execution_reports) 
	{
		std::string status;
		switch (exec_rep.getStatus())
		{
			case 0:
				status = "New";
				break;
			case 1:
				status = "Rejected";
				break;
			case 2:
				status = "Fill";
				break;
			case 3:
				status = "Pfill";
				break;
		}
		file << exec_rep.getOrderId() << ","
			<< exec_rep.getClientOrderId() << ","
			<< exec_rep.getInstrument() << ","
			<< exec_rep.getSide() << ","
			<< status << ","
			<< exec_rep.getQuantity() << ","
			<< exec_rep.getPrice() << "\n";
	}

	file.close();
	std::cout << "Orders written to file: " << file_path << std::endl;
}

void ExchangeApplication::addExecutionReport(ExecutionReport execution_report)
{
	execution_reports.push_back(execution_report);
}
