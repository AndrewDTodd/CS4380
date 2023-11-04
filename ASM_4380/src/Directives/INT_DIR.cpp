#include "../../include/Directives/INT_DIR.h"

#include <stdexcept>

INT_DIR::INT_DIR(): ASMDirective(".INT")
{}

size_t INT_DIR::Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The .INT directive expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const std::string& argument = args[0];

	//Match base ten with # as delimiter
	if (std::regex_match(argument, decimalPattern))
	{
		try
		{
			int32_t value = std::stoi(argument.substr(1));

			SerializeToBuffer<int32_t, int32_t>(value, workpiece);

			return sizeof(int32_t);
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("Cannot assign value to .INT outisde the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
				std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + argument.substr(1) + "\"");
		}
	}
	//Match Hex with 0x as delimiter
	else if (std::regex_match(argument, hexPattern))
	{
		try
		{
			if (argument[0] == '-')
			{
				int32_t value = std::stoi(argument, nullptr, 16);

				SerializeToBuffer<int32_t, int32_t>(value, workpiece);
			}
			else
			{
				unsigned long unsignedValue = std::stoul(argument, nullptr, 16);

				if (unsignedValue > std::numeric_limits<uint32_t>::max())
					throw std::out_of_range("");

				int32_t value = static_cast<int32_t>(unsignedValue);
				
				SerializeToBuffer<int32_t, int32_t>(value, workpiece);
			}

			return sizeof(int32_t);
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("Cannot assign value to .INT outisde the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
				std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + argument + "\" (" + std::to_string(std::stoll(argument, nullptr, 16)) + ")");
		}
	}
	//Match '*' with character enclosed in single quotes
	else if (std::regex_match(argument, asciiPattern))
	{
		SerializeToBuffer<int32_t, int32_t>(static_cast<int32_t>(argument[1]), workpiece);
	}
	else if (std::regex_match(argument, asciiEscape))
	{
		if (argument[2] == 'n')
		{
			SerializeToBuffer<int32_t, int32_t>(static_cast<int32_t>('\n'), workpiece);
		}
		else if (argument[2] == 't')
		{
			SerializeToBuffer<int32_t, int32_t>(static_cast<int32_t>('\t'), workpiece);
		}
		else
			throw std::runtime_error("Unsupported escape sequence \"" + argument.substr(1) + "\". Supported sequences are \\n and \\t");

		return sizeof(uint8_t);
	}
	//Did not match any expected argument types
	else
	{
		throw std::runtime_error("Unrecognized argument format for .INT directive \"" + argument + "\". Expected formats are -?#d+, or -?0xd+");
	}
}