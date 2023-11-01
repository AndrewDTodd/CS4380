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
		try
		{
			int value = std::stoi(argument.substr(1));
			if (value > 255 || value < 0)
				throw std::runtime_error("Cannot assign value to .BYT outisde the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
					std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + argument.substr(1) + "\"");

			workpiece->_dataSegmentBin.push_back(static_cast<uint8_t>(value));
			return sizeof(uint8_t);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("In BYT directive, invlaid_argument thrown when trying to convert argument to base ten int \"" + argument +
				"\"\n>>>" + argEx.what());
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("In BYT directive, out_of_range thrown when trying to convert argument to base ten int \"" + argument +
				"\". Your argument is way too big\n>>>" + rngEx.what());
		}
	}
	//Match Hex with 0x as delimiter
	else if (std::regex_match(argument, hexPattern))
	{
		try
		{
			int value = std::stoi(argument.substr(2), nullptr, 16);

			if (value > std::numeric_limits<uint8_t>::max() || value < std::numeric_limits<uint8_t>::min())
				throw std::runtime_error("Cannot assign value to .BYT outisde the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
					std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + argument + "\" (" + std::to_string(value) + ")");

			workpiece->_dataSegmentBin.push_back(static_cast<uint8_t>(value));
			return sizeof(uint8_t);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("In BYT directive, invlaid_argument thrown when trying to convert argument to base ten int \"" + argument +
				"\"\n>>>" + argEx.what());
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("In BYT directive, out_of_range thrown when trying to convert argument to base ten int \"" + argument +
				"\". Your argument is way too big\n>>>" + rngEx.what());
		}
	}
	//Match '*' with character enclosed in single quotes
	else if (std::regex_match(argument, asciiPattern))
	{
		workpiece->_dataSegmentBin.push_back(argument[1]);
		return sizeof(uint8_t);
	}
	else if (std::regex_match(argument, asciiEscape))
	{
		if (argument[2] == 'n')
		{
			workpiece->_dataSegmentBin.push_back('\n');
		}
		else if (argument[2] == 't')
		{
			workpiece->_dataSegmentBin.push_back('\t');
		}
		else
			throw std::runtime_error("In .BYT directive, unsupported escape sequence \"" + argument + "\". Supported sequences are \\n and \\t");

		return sizeof(uint8_t);
	}
	//Did not match any expected argument types
	else
	{
		throw std::runtime_error("Unrecognized argument format for .BYT directive \"" + argument + "\". Expected formats are #d+, 0xd+, '.', or '\\.'");
	}
}