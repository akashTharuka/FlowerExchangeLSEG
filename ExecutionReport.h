#pragma once
#include <string>
#include "Enums.h"

class ExecutionReport
{
	public:
		// parameters
		// order_id: This unique ID identifies the submitted order
		// status : { 0: New, 1: Rejected, 2: Fill, 3: Pfill }
		// reason : { Invalid Instrument, Invalid Side, Invalid Price, Invalid Quantity, Invalid Client Order ID, Invalid Transaction Time, Invalid Status }
		// transaction_time : YYYYMMDD-HH:MM:SS.sss
		ExecutionReport(std::string client_order_id, std::string instrument, int side, double price, int quantity, int status, std::string transaction_time, std::string reason = "");
		~ExecutionReport();

		// Getters
		std::string getClientOrderId() const { return client_order_id; }
		std::string getOrderId() const { return order_id; }
		std::string getInstrument() const { return instrument; }
		int getSide() const { return side; }
		double getPrice() const { return price; }
		int getQuantity() const { return quantity; }
		int getStatus() const { return status; }
		std::string getReason() const { return reason; }
		std::string getTransactionTime() const { return transaction_time; }

		// Setters
		void setOrderId(std::string order_id) { this->order_id = order_id; }
		void setStatus(int status) { this->status = status; }
		void setReason(std::string reason) { this->reason = reason; }

	private:
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

