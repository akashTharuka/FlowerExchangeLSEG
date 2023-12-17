#pragma once
#include "OrderBook.h"
#include <unordered_map>
#include "ExecutionReport.h"

class ExchangeApplication
{
	public:
		ExchangeApplication();
		~ExchangeApplication() {};

		void processOrdersCsvFile(std::string file_path);
		void writeToCsvFile(std::vector<ExecutionReport> execution_reports, std::string file_path);

		// Getters
		std::vector<ExecutionReport> getExecutionReports() const { return execution_reports; }

		static void addExecutionReport(ExecutionReport execution_report);

	private:
		static int order_id_counter;
		static const int MAX_INSTRUMENTS = 5;
		static std::vector<ExecutionReport> execution_reports;
		OrderBook order_books[MAX_INSTRUMENTS];
};

