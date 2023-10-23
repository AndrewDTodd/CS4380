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
			int64_t value = std::stoll(argument.substr(1));
			if (value > std::numeric_limits<int32_t>::max() || value < std::numeric_limits<int32_t>::min())
				throw std::runtime_error("Cannot assign value to .INT outisde the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
					std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + argument.substr(1) + "\"");

			SerializeToBuffer<int64_t, int32_t>(value, workpiece);

			return sizeof(int32_t);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("In INT directive, invlaid_argument thrown when trying to convert argument to base ten int \"" + argument +
				"\"\n>>>" + argEx.what());
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("In INT directive, out_of_range thrown when trying to convert argument to base ten int \"" + argument +
				"\". Your argument is way too big\n>>>" + rngEx.what());
		}
	}
	//Match Hex with 0x as delimiter
	else if (std::regex_match(argument, hexPattern))
	{
		try
		{
			int64_t value = std::stoll(argument.substr(2), nullptr, 16);
			if (value > std::numeric_limits<int32_t>::max() || value < std::numeric_limits<int32_t>::min())
				throw std::runtime_error("Cannot assign value to .INT outisde the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
					std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + argument + "\" (" + std::to_string(value) + ")");

			SerializeToBuffer<int64_t, int32_t>(value, workpiece);

			return sizeof(int32_t);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("In INT directive, invlaid_argument thrown when trying to convert argument to base ten int \"" + argument +
				"\"\n>>>" + argEx.what());
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("In INT directive, out_of_range thrown when trying to convert argument to base ten int \"" + argument +
				"\". Your argument is way too big\n>>>" + rngEx.what());
		}
	}
	//Did not match any expected argument types
	else
	{
		throw std::runtime_error("Unrecognized argument format for .INT directive \"" + argument + "\". Expected formats are #d+, or 0xd+");
	}
}