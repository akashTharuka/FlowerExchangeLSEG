#include "Utils.h"
#include <ctime>
#include <iostream>

// transaction time format : YYYYMMDD-HH:MM:SS.sss
std::string FlowerExchangeUtils::formatTransactionTime()
{
	time_t now = time(0);
	return std::to_string(now);
}
void FlowerExchangeUtils::printVector(std::vector<std::string> v)
{
	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}
