/**
*	Author: crylittlebear
*	Data: 2024-6-25
*/

#pragma once

#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

class TimeStamp {
	using SysLock = std::chrono::system_clock;
	using TimePoint = std::chrono::time_point<SysLock>;
public:
	static std::string now();
};

