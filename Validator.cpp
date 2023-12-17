#include "Validator.h"
#include <regex>
#include "Enums.h"

bool Validator::isValidClientOrderId(const std::string& client_order_id)
{
	// only alphanumeric char with min 1 max 7
	std::string client_order_id_pattern = "^[a-zA-Z0-9]{1,7}$";
	return std::regex_match(client_order_id, std::regex(client_order_id_pattern));
}

bool Validator::isValidInstrument(const std::string& instrument)
{
	// should only include { Rose, Lavender, Lotus, Tulip, Orchid }
	std::string instrument_pattern = "^(Rose|Lavender|Lotus|Tulip|Orchid)$";
	return std::regex_match(instrument, std::regex(instrument_pattern));
}

bool Validator::isValidSide(int side)
{
	// should only include { Buy, Sell }
	return side == Side::BUY + 1 || side == Side::SELL + 1;
}

bool Validator::isValidPrice(double price)
{
	// should be a positive double
	return price > 0;
}

bool Validator::isValidQuantity(int quantity)
{
	// should be a positive integer multiple of 10, min 10 max 1000
	return quantity % 10 == 0 && quantity >= 10 && quantity <= 1000;
}

std::string Validator::validate(const std::string& client_order_id, const std::string& instrument, int side, double price, int quantity)
{
	if (!isValidClientOrderId(client_order_id))
	{
		return "Invalid client order id";
	}
	if (!isValidInstrument(instrument))
	{
		return "Invalid instrument";
	}
	if (!isValidSide(side))
	{
		return "Invalid side";
	}
	if (!isValidPrice(price))
	{
		return "Invalid price";
	}
	if (!isValidQuantity(quantity))
	{
		return "Invalid quantity";
	}
	return "";
}