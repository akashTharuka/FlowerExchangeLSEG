#pragma once
#include <string>

class Validator
{
	public:
		Validator() {};
		~Validator() {};
		static std::string validate(const std::string& client_order_id, const std::string& instrument, int side, double price, int quantity);
	private:
		static bool isValidClientOrderId(const std::string& clientOrderId);
		static bool isValidInstrument(const std::string& instrument);
		static bool isValidSide(int side);
		static bool isValidPrice(double price);
		static bool isValidQuantity(int quantity);

};

