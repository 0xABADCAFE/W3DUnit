#ifndef _W3DTEST_LOGGER_HPP_
#	define _W3DTEST_LOGGER_HPP_

#include <cstdio>
#include <cstdarg>

class Log {
	public:
		static void write(const char* fmt, ...);
		static bool open(const char* name);
		static void close();
	private:
		static std::FILE* logFile;
};

#endif
