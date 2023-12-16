#include "ExchangeApplication.h"

int main()
{
	const std::string INPUT_PATH = "input/order.csv";
	const std::string OUTPUT_PATH = "output/execution_rep.csv";

	ExchangeApplication app;
	app.processOrdersCsvFile(INPUT_PATH);
	app.writeToCsvFile(app.getExecutionReports(), OUTPUT_PATH);

	return 0;
}