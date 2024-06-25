/**
*	Author: crylittlebear
*	Data: 2024-6-25
*/

#include <iostream>
#include <chrono>

#include "Logger.h"
#include "TimeStamp.h"

Logger& Logger::instance() {
	static Logger log;
	return log;
}

void Logger::setLogLevel(int level) {
	logLevel_ = level;
}

void Logger::log(const std::string& msg) {
	switch (logLevel_) {
	case LogLevel::Info:
		std::cout << "[INFO]-";
		break;
	case LogLevel::Error:
		std::cout << "[ERROR]-";
		break;
	case LogLevel::Fatal:
		std::cout << "[FATAL]-";
		break;
	case LogLevel::Debug:
		std::cout << "[DEBUG]-";
		break;
	default:
		break;
	}
	std::cout << TimeStamp::now() << "--(" << msg  << ")" << std::endl;
}