#include "pch.h"
#include "Core/Log.h"
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
using namespace Anim;

/* asci escape codes to change terminal print-color on Linux systems */
#define CONSOLE_COLOR_RED     "\x1b[1;31m"
#define CONSOLE_COLOR_GREEN   "\x1b[32m"
#define CONSOLE_COLOR_YELLOW  "\x1b[01;33m"
#define CONSOLE_COLOR_BLUE    "\x1b[34m"
#define CONSOLE_COLOR_MAGENTA "\x1b[1;35m"
#define CONSOLE_COLOR_CYAN    "\x1b[0;36m"

#define CONSOLE_COLOR_BOLD_WHITE "\x1b[97m"
#define CONSOLE_BG_COLOR_RED "\x1b[41m"

#define CONSOLE_COLOR_RESET   "\x1b[0m"


std::string GetSystemTime()
{
	time_t currentTime;
	time(&currentTime);
	
	struct tm* timeInfo = localtime(&currentTime);

	std::stringstream ss;

	if (timeInfo->tm_hour < 10)
	{
		ss << "0" << timeInfo->tm_hour;
	} else {
		ss << timeInfo->tm_hour;
	}
	if (timeInfo->tm_min < 10)
	{
		ss << ":0" << timeInfo->tm_min;
	} else {
		ss << ":" << timeInfo->tm_min;
	}
	if (timeInfo->tm_sec < 10)
	{
		ss << ":0" << timeInfo->tm_sec;
	} else {
		ss << ":" << timeInfo->tm_sec;
	}

	return ss.str();
}


void Log::Info(const char* msg)
{
	printf("|%s| %s\n", GetSystemTime().c_str(), msg);
}

void Log::Warn(const char* msg)
{
	printf(CONSOLE_COLOR_YELLOW "|%s| %s\n" CONSOLE_COLOR_RESET, GetSystemTime().c_str(), msg);
}

void Log::Error(const char* msg)
{
	printf(CONSOLE_COLOR_RED "|%s| %s\n" CONSOLE_COLOR_RESET, GetSystemTime().c_str(), msg);
}

void Log::Crit(const char* msg)
{
	printf(CONSOLE_BG_COLOR_RED CONSOLE_COLOR_BOLD_WHITE "|%s| %s\n" CONSOLE_COLOR_RESET, GetSystemTime().c_str(), msg);
}

