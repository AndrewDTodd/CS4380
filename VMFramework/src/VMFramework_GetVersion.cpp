#include "../include/VMFramework_GetVersion.h"

#include <sstream>

namespace VMFramework
{
	std::string GetFrameworkVersion()
	{
		std::stringstream versionStream;
		versionStream << "VMFramework v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;

		return versionStream.str();
	}
}