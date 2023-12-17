#include "Utils.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

// transaction time format : YYYYMMDD-HH:MM:SS.sss
std::string FlowerExchangeUtils::getTransactionTime()
{
    std::time_t now = std::time(nullptr);
    std::tm ltm;

#ifdef _MSC_VER // Check if using Microsoft Visual Studio
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&ltm, "%Y%m%d-%H:%M:%S.000");

    return oss.str();
}
void FlowerExchangeUtils::printVector(std::vector<std::string> v)
{
	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}
