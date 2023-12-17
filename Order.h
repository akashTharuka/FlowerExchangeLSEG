#pragma once
#include <string>

class Order
{
	public:
		// parameters
		// client_order_id: This unique ID identifies the submitted order
		// instrument: { Rose, Lavender, Lotus, Tulip, Orchid }
		// side: { 1: Buy, 2: Sell }
		// price: The unit price > 0.0
		// quantity: Order size must be a a multiple of 10. Min 10, Max 1000
		Order(const std::string& client_order_id, const std::string& instrument, int side, double price, int quantity);
		~Order();

		// Getters
		std::string getClientOrderId() const { return client_order_id; }
		std::string getInstrument() const { return instrument; }
		int getSide() const { return side; }
		double getPrice() const { return price; }
		int getQuantity() const { return quantity; }

		// Setters
		void setQuantity(int quantity) { this->quantity = quantity; }

	private:
		std::string client_order_id;
		std::string instrument;
		int side;
		double price;
		int quantity;
};

