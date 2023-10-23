#include "../../include/Directives/BYT_DIR.h"

#include <stdexcept>
#include <regex>
#include <string>
#include <utility>

BYT_DIR::BYT_DIR(): ASMDirective(".BYT")
{}

size_t BYT_DIR::Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The .BYT directive expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const std::string& argument = args[0];

	//Match base ten with # as delimiter
	if (std::regex_match(argument, decimalPattern))
	{
		int value = std::stoi(argument.substr(1));
		if (value > 255 || value < 0)
			throw std::runtime_error("Cannot assign value to .BYT outisde the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
				std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + argument.substr(1) + "\"");

		workpiece->_dataSegmentBin.push_back(static_cast<uint8_t>(value));
		return sizeof(uint8_t);
	}
	//Match Hex with 0x as delimiter
	else if (std::regex_match(argument, hexPattern))
	{
		int value = std::stoi(argument.substr(2), nullptr, 16);

		if (value > std::numeric_limits<uint8_t>::max() || value < std::numeric_limits<uint8_t>::min())
			throw std::runtime_error("Cannot assign value to .BYT outisde the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " + 
				std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + argument + "\" (" + std::to_string(value) + ")");

		workpiece->_dataSegmentBin.push_back(static_cast<uint8_t>(value));
		return sizeof(uint8_t);
	}
	//Match '*' with character enclosed in single quotes
	else if (std::regex_match(argument, asciiPattern))
	{
		workpiece->_dataSegmentBin.push_back(argument[1]);
		return sizeof(uint8_t);
	}
	//Did not match any expected argument types
	else
	{
		throw std::runtime_error("Unrecognized argument format for .BYT directive \"" + argument + "\"");
	}
}