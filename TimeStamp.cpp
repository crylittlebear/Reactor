#include "TimeStamp.h"

std::string TimeStamp::now() {
	std::time_t tt = SysLock::to_time_t(SysLock::now());
	std::tm t = *std::localtime(&tt);
	t.tm_hour += 8;
	mktime(&t);
	std::ostringstream oss;
	oss << std::put_time(&t, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}