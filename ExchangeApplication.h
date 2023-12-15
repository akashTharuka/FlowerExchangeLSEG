#pragma once
#include "OrderBook.h"
#include <unordered_map>

class ExchangeApplication
{
	public:
		ExchangeApplication();
		~ExchangeApplication();

		std::string generateUniqueOrderId();
		void processOrdersCsvFile(std::string file_path);

		// Getters
		// OrderBook& getOrderBook(std::string instrument) { return order_books[instrument]; }

	private:
		static int order_id_counter;
		static const int MAX_INSTRUMENTS = 5;
		// std::unordered_map<std::string, OrderBook> order_books;
		OrderBook order_books[MAX_INSTRUMENTS];
};

