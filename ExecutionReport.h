#pragma once
#include <string>
#include "Enums.h"

struct ExecutionReport
{
	std::string client_order_id;
	std::string order_id;
	std::string instrument;
	int side;
	double price;
	int quantity;
	int status;
	std::string reason;
	std::string transaction_time;
};
