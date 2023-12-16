#include "ExecutionReport.h"
#include <iostream>

ExecutionReport::ExecutionReport(const std::string client_order_id, std::string order_id, const std::string instrument, int side, double price, int quantity, int status, std::string transaction_time, std::string reason)
{
	this->client_order_id = client_order_id;
	this->order_id = order_id;
	this->instrument = instrument;
	this->side = side;
	this->price = price;
	this->quantity = quantity;
	this->status = status;
	this->reason = reason;
	this->transaction_time = transaction_time;
}

ExecutionReport::~ExecutionReport()
{
	// Cleanup or resource release code here
}
