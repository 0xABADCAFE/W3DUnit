
#include "logger.hpp"

std::FILE* Log::logFile = 0;

void Log::write(const char* fmt, ...)
{
	if (logFile) {
		va_list argList;
		va_start(argList, fmt);
		std::vfprintf(logFile, fmt, argList);
		std::fflush(logFile);
		va_end(argList);
	}
}

bool Log::open(const char* name)
{
	return (logFile = std::fopen(name, "w"));
}

void Log::close()
{
	if (logFile) {
		std::fclose(logFile);
		logFile = 0;
	}
}
