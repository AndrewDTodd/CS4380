#include "../../include/Directives/STR_DIR.h"

#include <stdexcept>
#include <regex>
#include <string>
#include <utility>

STR_DIR::STR_DIR() : ASMDirective(".STR")
{}

size_t STR_DIR::Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() > 1)
		throw std::runtime_error("The .STR directive expects one or no argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	if (args.size() == 0)
	{
		workpiece->_dataSegmentBin.push_back(0);

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

		workpiece->_dataSegmentBin.push_back(static_cast<uint8_t>(argLength));

		std::copy(cstr, cstr + argLength, std::back_inserter(workpiece->_dataSegmentBin));
	}
	//Did not match any expected argument types
	else
	{
		throw std::runtime_error("Unrecognized argument format for .CSTR directive \"" + argument + "\". Expected format is characters surrounded by \"\"");
	}

	return sizeof(uint8_t) * argLength + 1;
}