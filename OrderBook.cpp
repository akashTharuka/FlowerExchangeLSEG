#include "OrderBook.h"
#include <iostream>
#include "ExecutionReport.h"
#include "ExchangeApplication.h"

OrderBook::OrderBook(const std::string& instrument)
{
	this->instrument = instrument;
}

OrderBook::~OrderBook()
{
}

void OrderBook::addBuyOrder(Order buy_order, const std::string& order_id)
{
	ExecutionReport exec_rep;

	// if sell_orders is empty or no match found, directly add the buy order to buy_orders
	if (this->sell_orders.empty() || buy_order.getPrice() <= this->sell_orders.begin()->second[0].getPrice())
	{
		this->buy_orders[buy_order.getPrice()].push_back(buy_order);
		// exec report for the buy order with status="NEW" with min_sell_price and min_sell_quantity
		ExecutionReport exec_rep = ExecutionReport(
			buy_order.getClientOrderId(), 
			order_id, 
			buy_order.getInstrument(), 
			buy_order.getSide(), 
			buy_order.getPrice(), 
			buy_order.getQuantity(),
			ExecutionStatus::New, 
			"transaction_time", 
			""
		);
		ExchangeApplication::addExecutionReport(exec_rep);
		return;
	}

	auto iterator = this->sell_orders.begin();
	Order curr_sell_order = iterator->second[0];

	while (buy_order.getPrice() >= curr_sell_order.getPrice())
	{
		if (buy_order.getQuantity() > curr_sell_order.getQuantity())
		{
			// update the buy order quantity
			buy_order.setQuantity(buy_order.getQuantity() - curr_sell_order.getQuantity());
			// exec report for the buy order with status="PFILL" with min_sell_price and min_sell_quantity
			exec_rep = ExecutionReport(
				buy_order.getClientOrderId(), 
				order_id, 
				buy_order.getInstrument(), 
				buy_order.getSide(), 
				curr_sell_order.getPrice(),
				curr_sell_order.getQuantity(),
				ExecutionStatus::Pfill, 
				"transaction_time", 
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			this->sell_orders[curr_sell_order.getPrice()].erase(this->sell_orders[curr_sell_order.getPrice()].begin());
			// exec report for the sell order with status="FILL" with min_sell_price and min_sell_quantity
			exec_rep = ExecutionReport(
				curr_sell_order.getClientOrderId(), 
				order_id, 
				curr_sell_order.getInstrument(),
				curr_sell_order.getSide(),
				curr_sell_order.getPrice(),
				curr_sell_order.getQuantity(),
				ExecutionStatus::Fill, 
				"transaction_time", 
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);

			return;
		}
		else if (buy_order.getQuantity() < curr_sell_order.getQuantity())
		{
			// since buy order is completed, no need to update the buy_orders
			// exec report for the buy order with status="FILL" with min_sell_price and curr_buy_order.getQuantity()
			exec_rep = ExecutionReport(
				buy_order.getClientOrderId(), 
				order_id, 
				buy_order.getInstrument(), 
				buy_order.getSide(), 
				curr_sell_order.getPrice(),
				buy_order.getQuantity(), 
				ExecutionStatus::Fill, 
				"transaction_time", 
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			// update the sell order quantity
			this->sell_orders[curr_sell_order.getPrice()][0].setQuantity(curr_sell_order.getQuantity() - buy_order.getQuantity());
			// exec report for the sell order with status="PFILL" with min_sell_price and curr_buy_order.getQuantity()
			exec_rep = ExecutionReport(
				curr_sell_order.getClientOrderId(), 
				order_id, 
				curr_sell_order.getInstrument(),
				curr_sell_order.getSide(),
				curr_sell_order.getPrice(),
				curr_sell_order.getQuantity(),
				ExecutionStatus::Pfill, 
				"transaction_time", 
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			
			return;
		}
		else
		{
			// since buy order is completed, no need to update the buy_orders
			// exec report for the buy order with status="FILL" with min_sell_price and curr_buy_order.getQuantity()
			exec_rep = ExecutionReport(
				buy_order.getClientOrderId(), 
				order_id, 
				buy_order.getInstrument(), 
				buy_order.getSide(), 
				curr_sell_order.getPrice(),
				buy_order.getQuantity(), 
				ExecutionStatus::Fill, 
				"transaction_time", 
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			// since sell order is also completed, remove the sell order from the sell_orders
			this->sell_orders[curr_sell_order.getPrice()].erase(this->sell_orders[curr_sell_order.getPrice()].begin());
			// exec report for the sell order with status="FILL" with min_sell_price and curr_buy_order.getQuantity()
			exec_rep = ExecutionReport(
				curr_sell_order.getClientOrderId(),
				order_id, 
				curr_sell_order.getInstrument(),
				curr_sell_order.getSide(),
				curr_sell_order.getPrice(),
				buy_order.getQuantity(), 
				ExecutionStatus::Fill, 
				"transaction_time", 
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);

			return;
		}

		if (this->sell_orders[curr_sell_order.getPrice()].empty())
		{
			this->sell_orders.erase(curr_sell_order.getPrice());
			if (this->sell_orders.empty())
			{
				this->buy_orders[buy_order.getPrice()].push_back(buy_order);
				return;
			}
		}
		iterator = this->sell_orders.begin();
		curr_sell_order = iterator->second[0];
	}

	// no matching sell order found for the remaining quantity, add the buy order to buy_orders
	this->buy_orders[buy_order.getPrice()].push_back(buy_order);
}

void OrderBook::addSellOrder(Order sell_order, const std::string& order_id)
{
	ExecutionReport exec_rep;

	// if buy_orders is empty or no match found, directly add the sell order to sell_orders
	if (this->buy_orders.empty() || sell_order.getPrice() >= this->buy_orders.begin()->second[0].getPrice())
	{
		this->sell_orders[sell_order.getPrice()].push_back(sell_order);
		//std::cout << "sell orders size:" << sell_orders.size() << std::endl;
		// exec report for the sell order with status="NEW" with min_buy_price and min_buy_quantity
		ExecutionReport exec_rep = ExecutionReport(
			sell_order.getClientOrderId(),
			order_id,
			sell_order.getInstrument(),
			sell_order.getSide(),
			sell_order.getPrice(),
			sell_order.getQuantity(),
			ExecutionStatus::New,
			"transaction_time",
			""
		);
		ExchangeApplication::addExecutionReport(exec_rep);
		return;
	}

	auto iterator = this->buy_orders.begin();
	Order curr_buy_order = iterator->second[0];

	while (sell_order.getPrice() <= curr_buy_order.getPrice())
	{
		if (sell_order.getQuantity() > curr_buy_order.getQuantity())
		{
			// update the sell order quantity
			sell_order.setQuantity(sell_order.getQuantity() - curr_buy_order.getQuantity());
			// exec report for the sell order with status="PFILL" with min_buy_price and min_buy_quantity
			exec_rep = ExecutionReport(
				sell_order.getClientOrderId(),
				order_id,
				sell_order.getInstrument(),
				sell_order.getSide(),
				curr_buy_order.getPrice(),
				curr_buy_order.getQuantity(),
				ExecutionStatus::Pfill,
				"transaction_time",
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			this->buy_orders[curr_buy_order.getPrice()].erase(this->buy_orders[curr_buy_order.getPrice()].begin());
			// exec report for the buy order with status="FILL" with min_buy_price and min_buy_quantity
			exec_rep = ExecutionReport(
				curr_buy_order.getClientOrderId(),
				order_id,
				curr_buy_order.getInstrument(),
				curr_buy_order.getSide(),
				curr_buy_order.getPrice(),
				curr_buy_order.getQuantity(),
				ExecutionStatus::Fill,
				"transaction_time",
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
		}
		else if (sell_order.getQuantity() < curr_buy_order.getQuantity())
		{
			// since sell order is completed, no need to update the sell_orders
			// exec report for the sell order with status="FILL" with min_buy_price and sell_order.getQuantity()
			exec_rep = ExecutionReport(
				sell_order.getClientOrderId(),
				order_id,
				sell_order.getInstrument(),
				sell_order.getSide(),
				curr_buy_order.getPrice(),
				sell_order.getQuantity(),
				ExecutionStatus::Fill,
				"transaction_time",
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			// update the buy order quantity
			this->buy_orders[curr_buy_order.getPrice()][0].setQuantity(curr_buy_order.getQuantity() - sell_order.getQuantity());
			// exec report for the buy order with status="PFILL" with min_buy_price and sell_order.getQuantity()
			exec_rep = ExecutionReport(
				curr_buy_order.getClientOrderId(),
				order_id,
				curr_buy_order.getInstrument(),
				curr_buy_order.getSide(),
				curr_buy_order.getPrice(),
				curr_buy_order.getQuantity(),
				ExecutionStatus::Pfill,
				"transaction_time",
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
		}
		else
		{
			// since sell order is completed, no need to update the sell_orders
			// exec report for the sell order with status="FILL" with min_buy_price and sell_order.getQuantity()
			exec_rep = ExecutionReport(
				sell_order.getClientOrderId(),
				order_id,
				sell_order.getInstrument(),
				sell_order.getSide(),
				curr_buy_order.getPrice(),
				sell_order.getQuantity(),
				ExecutionStatus::Fill,
				"transaction_time",
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
			// since buy order is also completed, remove the buy order from the buy_orders
			this->buy_orders[curr_buy_order.getPrice()].erase(this->buy_orders[curr_buy_order.getPrice()].begin());
			// exec report for the buy order with status="FILL" with min_buy_price and sell_order.getQuantity()
			exec_rep = ExecutionReport(
				curr_buy_order.getClientOrderId(),
				order_id,
				curr_buy_order.getInstrument(),
				curr_buy_order.getSide(),
				curr_buy_order.getPrice(),
				sell_order.getQuantity(),
				ExecutionStatus::Fill,
				"transaction_time",
				""
			);
			ExchangeApplication::addExecutionReport(exec_rep);
		}

		if (this->buy_orders[curr_buy_order.getPrice()].empty())
		{
			this->buy_orders.erase(curr_buy_order.getPrice());
			if (this->buy_orders.empty())
			{
				this->sell_orders[sell_order.getPrice()].push_back(sell_order);
				return;
			}
		}
		iterator = this->buy_orders.begin();
		curr_buy_order = iterator->second[0];
	}
	
	// no matching buy order found for the remaining quantity, add the sell order to sell_orders
	this->sell_orders[sell_order.getPrice()].push_back(sell_order);
}
