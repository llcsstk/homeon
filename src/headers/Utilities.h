#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <time.h>

namespace Util
{
	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	const std::string CurrentDateTime()
	{
		time_t rawtime;
		struct tm * timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		return asctime(timeinfo);
	}
}
#endif