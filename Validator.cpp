#include "Validator.h"
#include <regex>
#include "Enums.h"

namespace Validator
{
	bool isValidClientOrderId(const std::string& client_order_id)
	{
		// only alphanumeric char with min 1 max 7
		std::string client_order_id_pattern = "^[a-zA-Z0-9]{1,7}$";
		return std::regex_match(client_order_id, std::regex(client_order_id_pattern));
	}
	bool isValidInstrument(const std::string& instrument)
	{
		// should only include { Rose, Lavender, Lotus, Tulip, Orchid }
		std::string instrument_pattern = "^(Rose|Lavender|Lotus|Tulip|Orchid)$";
		return std::regex_match(instrument, std::regex(instrument_pattern));
	}
	bool isValidSide(const std::string& side_string)
	{
		// should only include { Buy, Sell }
		std::string side_string_pattern = "^(Buy|Sell)$";
		return std::regex_match(side_string, std::regex(side_string_pattern));
	}
	bool isValidPrice(double price)
	{
		// should be a positive double
		return price > 0;
	}
	bool isValidQuantity(int quantity)
	{
		// should be a positive integer multiple of 10, min 10 max 1000
		return quantity % 10 == 0 && quantity >= 10 && quantity <= 1000;
	}
}
