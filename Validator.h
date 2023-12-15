#pragma once
#include <string>

namespace Validator
{
	bool isValidClientOrderId(const std::string& clientOrderId);
	bool isValidInstrument(const std::string& instrument);
	bool isValidSide(const std::string& side_string);
	bool isValidPrice(double price);
	bool isValidQuantity(int quantity);
}

