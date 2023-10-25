#include "../include/ASMFramework_GetVersion.h"

#include <sstream>

namespace ASMFramework
{
	std::string GetFrameworkVersion()
	{
		std::stringstream versionStream;
		versionStream << "ASMFramework v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;

		return versionStream.str();
	}
}