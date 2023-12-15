#include "ExecutionReport.h"
#include <iostream>

ExecutionReport::ExecutionReport(std::string client_order_id, std::string instrument, int side, double price, int quantity, int status, std::string reason, std::string transaction_time)
{
	this->client_order_id = client_order_id;
	//this->order_id = ;
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
	std::cout << "Destructor called" << std::endl;
	// Cleanup or resource release code here
}
