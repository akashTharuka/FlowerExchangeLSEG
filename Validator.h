#pragma once
#include <string>

class Validator
{
	public:
		Validator();
		~Validator();

		static bool isValidClientOrderId(const std::string& client_order_id);
		static bool isValidInstrument(const std::string& instrument);
		static bool isValidSide(int side);
		static bool isValidPrice(double price);
		static bool isValidQuantity(int quantity);
};

