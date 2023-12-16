#pragma once
#include "OrderBook.h"
#include <unordered_map>
#include "ExecutionReport.h"

class ExchangeApplication
{
	public:
		ExchangeApplication();
		~ExchangeApplication();

		std::string generateUniqueOrderId();
		void processOrdersCsvFile(std::string file_path);
		void writeToCsvFile(std::vector<ExecutionReport> execution_reports, std::string file_path);

		// Getters
		// OrderBook& getOrderBook(std::string instrument) { return order_books[instrument]; }
		std::vector<ExecutionReport> getExecutionReports() const { return execution_reports; }

		void addExecutionReport(ExecutionReport execution_report);

	private:
		static int order_id_counter;
		static const int MAX_INSTRUMENTS = 5;
		// std::unordered_map<std::string, OrderBook> order_books;
		OrderBook order_books[MAX_INSTRUMENTS];
		std::vector<ExecutionReport> execution_reports;
};

