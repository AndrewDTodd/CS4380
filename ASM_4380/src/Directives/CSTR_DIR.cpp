#include "../../include/Directives/CSTR_DIR.h"

#include <stdexcept>
#include <regex>
#include <string>
#include <utility>

CSTR_DIR::CSTR_DIR() : ASMDirective(".CSTR")
{}

size_t CSTR_DIR::Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() > 1)
		throw std::runtime_error("The .CSTR directive expects one or no argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	if (args.size() == 0)
	{
		workpiece->_dataSegmentBin.push_back('\0');

		return sizeof(uint8_t);
	}

	const std::string& argument = args[0];
	std::string newArg = argument.substr(1, argument.size() - 2);

	size_t argLength = newArg.size();
	if (argLength > std::numeric_limits<uint8_t>::max())
		throw std::runtime_error("The system only supports strings of 255 characters or less. Provided argument has " + std::to_string(argLength) + "characters");

	//Match with string regex to verify we have a valid argument
	if (std::regex_match(argument, stringPattern))
	{
		const char* cstr = newArg.c_str();

		std::copy(cstr, cstr + argLength + 1, std::back_inserter(workpiece->_dataSegmentBin));
	}
	//Did not match any expected argument types
	else
	{
		throw std::runtime_error("Unrecognized argument format for .CSTR directive \"" + argument + "\". Expected format is characters surrounded by \"\"");
	}

	return sizeof(uint8_t) * argLength + 1;
}