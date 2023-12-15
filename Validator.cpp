#include "Validator.h"

Validator::Validator()
{
}

Validator::~Validator()
{
}

bool Validator::isValidClientOrderId(const std::string& client_order_id)
{
	return false;
}

bool Validator::isValidInstrument(const std::string& instrument)
{
	return false;
}

bool Validator::isValidSide(int side)
{
	return false;
}

bool Validator::isValidPrice(double price)
{
	return false;
}

bool Validator::isValidQuantity(int quantity)
{
	return false;
}
