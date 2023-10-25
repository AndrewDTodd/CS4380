#include "../../../include/Instructions/TRP/TRP.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "../../../include/Process_4380.h"

const std::regex TRP::hexPattern = std::regex(R"delim((^0x[0-9a-fA-F]+$))delim", std::regex_constants::ECMAScript);
const std::regex TRP::asciiPattern = std::regex(R"delim((^'.'$)|(^'\\[tnr]'$))delim", std::regex_constants::ECMAScript);

TRP::TRP() : Instruction(21)
{}

void TRP::Op(Process_4380* executingProcess)
{
	std::string input;

	switch (executingProcess->operandOne)
	{
	case (0):
		executingProcess->Stop();
		break;

	case (1):
		std::cout << executingProcess->m_registers[3];
		break;

	case(2):
		std::cin >> input;

		//Match Hex with 0x as delimiter
		if (std::regex_match(input, hexPattern))
		{
			try
			{
				int64_t value = std::stoll(input.substr(2), nullptr, 16);
				if (value > std::numeric_limits<int32_t>::max() || value < std::numeric_limits<int32_t>::min())
					throw std::runtime_error("Cannot assign integer value to register outisde the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
						std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + input + "\" (" + std::to_string(value) + ")");

				executingProcess->m_registers[3] = static_cast<int32_t>(value);
			}
			catch (const std::invalid_argument& argEx)
			{
				throw std::runtime_error("invlaid_argument, cannot convert input - \"" + input + "\" - to integer\n>>>" + argEx.what());
			}
			break;
		}
		try
		{
			int64_t value = std::stoll(input);
			if (value > std::numeric_limits<int32_t>::max() || value < std::numeric_limits<int32_t>::min())
				throw std::runtime_error("Cannot assign integer value to register outisde the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
					std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + input + "\"");

			executingProcess->m_registers[3] = static_cast<int32_t>(value);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("invlaid_argument, cannot convert input - \"" + input + "\" - to integer\n>>>" + argEx.what());
		}
		break;

	case(3):
		//Extract lowest byte from R3
		std::cout << static_cast<char>(executingProcess->m_registers[3] & 0xFF);
		break;

	case(4):
		std::cin >> input;

		//Match Hex with 0x as delimiter
		if (std::regex_match(input, hexPattern))
		{
			try
			{
				int value = std::stoi(input.substr(2), nullptr, 16);

				if (value > std::numeric_limits<uint8_t>::max() || value < std::numeric_limits<uint8_t>::min())
					throw std::runtime_error("Cannot assign byte value to register outisde the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
						std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + input + "\" (" + std::to_string(value) + ")");
			}
			catch (const std::invalid_argument& argEx)
			{
				throw std::runtime_error("invlaid_argument, cannot convert input - \"" + input + "\" - to byte\n>>>" + argEx.what());
			}
			break;
		}
		//Match '*' with character enclosed in single quotes
		else if (std::regex_match(input, asciiPattern))
		{
			executingProcess->m_registers[3] = static_cast<int32_t>(input[1]);
			break;
		}
		try
		{
			int value = std::stoi(input);
			if (value > std::numeric_limits<uint8_t>::max() || value < std::numeric_limits<uint8_t>::min())
				throw std::runtime_error("Cannot assign byte value to register outisde the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
					std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + input + "\"");

			executingProcess->m_registers[3] = static_cast<int32_t>(value);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("invlaid_argument, cannot convert input - \"" + input + "\" - to byte\n>>>" + argEx.what());
		}
		break;

	default:
		throw std::runtime_error("Invalid trap code detected: " + std::to_string(executingProcess->operandOne));
	}
}