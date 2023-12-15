#include "ExchangeApplication.h"
#include "Validator.h"
#include <iostream>

int main()
{
	const std::string INPUT_PATH = "input/order.csv";
	const std::string OUTPUT_PATH = "output/orders.csv";

	ExchangeApplication app;
	app.processOrdersCsvFile(INPUT_PATH);

	return 0;
}