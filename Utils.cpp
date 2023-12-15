#include "Utils.h"
#include <ctime>

namespace FlowerExchangeUtils
{
	// transaction time format : YYYYMMDD-HH:MM:SS.sss
	std::string formatTransactionTime()
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		std::string year = std::to_string(1900 + ltm->tm_year);
		std::string month = std::to_string(1 + ltm->tm_mon);
		std::string day = std::to_string(ltm->tm_mday);
		std::string hour = std::to_string(ltm->tm_hour);
		std::string minute = std::to_string(ltm->tm_min);
		std::string second = std::to_string(ltm->tm_sec);
		std::string millisecond = std::to_string(0);
		std::string transaction_time = year + month + day + "-" + hour + ":" + minute + ":" + second + "." + millisecond;
		return transaction_time;
	}
}
