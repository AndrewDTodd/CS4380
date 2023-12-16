#include "../../../include/Instructions/TRP/TRP.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "../../../include/Process_4380.h"

const std::regex TRP::hexPattern = std::regex(R"delim((^-?0x[0-9a-fA-F]+$))delim", std::regex_constants::ECMAScript);
const std::regex TRP::asciiPattern = std::regex(R"delim((^'.'$)|(^'\\[tnr]'$))delim", std::regex_constants::ECMAScript);

TRP::TRP() : Instruction(21)
{}

void TRP::Op(Process_4380* executingProcess)
{
	uint8_t placeholder = 0;
	std::string input;
	uint8_t* heapStrPtr;
	uint8_t* str;
	uint8_t& length = placeholder;
	size_t strLength;
	char* cstrPtr;

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
				if (input[0] == '-')
				{
					int32_t value = std::stoi(input, nullptr, 16);

					executingProcess->m_registers[3] = value;
				}
				else
				{
					unsigned long unsignedValue = std::stoul(input, nullptr, 16);

					if (unsignedValue > std::numeric_limits<uint32_t>::max())
						throw std::out_of_range("");

					int32_t value = static_cast<int32_t>(unsignedValue);
					
					executingProcess->m_registers[3] = value;
				}
			}
			catch (const std::invalid_argument& argEx)
			{
				throw std::runtime_error("invalid_argument thrown when trying to convert input to base ten int \"" + input +
					"\"\n>>>" + argEx.what());
			}
			catch (const std::out_of_range& rngEx)
			{
				throw std::runtime_error("Cannot assign integer value to register outside the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
					std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + input + "\" (" + std::to_string(std::stoll(input, nullptr, 16)) + ")");
			}
			break;
		}
		try
		{
			int32_t value = std::stoi(input);

			executingProcess->m_registers[3] = value;
			break;
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("invalid_argument thrown when trying to convert input to base ten int \"" + input +
				"\"\n>>>" + argEx.what());
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("Cannot assign integer value to register outside the range of " + std::to_string(std::numeric_limits<int32_t>::min()) + " - " +
				std::to_string(std::numeric_limits<int32_t>::max()) + " inclusive. Argument was \"" + input + "\"");
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
				unsigned long value = std::stoul(input, nullptr, 16);

				if (value > std::numeric_limits<uint8_t>::max())
					throw std::runtime_error("Cannot assign byte value to register outside the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
						std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + input + "\" (" + std::to_string(value) + ")");

				executingProcess->m_registers[3] = static_cast<uint8_t>(value);
				break;
			}
			catch (const std::out_of_range& rngEx)
			{
				throw std::runtime_error("out_of_range thrown when trying to convert input to byte \"" + input +
					"\". Your argument is way too big\n>>>" + rngEx.what());
			}
		}
		//Match '*' with character enclosed in single quotes or '\*' with escape character
		else if (std::regex_match(input, asciiPattern))
		{
			executingProcess->m_registers[3] = input[1];
			break;
		}
		try
		{
			unsigned long value = std::stoul(input);
			
			if (value > std::numeric_limits<uint8_t>::max())
				throw std::runtime_error("Cannot assign byte value to register outside the range of " + std::to_string(std::numeric_limits<uint8_t>::min()) + " - " +
					std::to_string(std::numeric_limits<uint8_t>::max()) + " inclusive. Argument was \"" + input + "\"");

			executingProcess->m_registers[3] = static_cast<uint8_t>(value);
		}
		catch (const std::invalid_argument& argEx)
		{
			throw std::runtime_error("invalid_argument, cannot convert input - \"" + input + "\" - to byte\n>>>" + argEx.what());
		}
		catch (const std::out_of_range& rngEx)
		{
			throw std::runtime_error("out_of_range thrown when trying to convert input to byte \"" + input +
				"\". Your argument is way too big\n>>>" + rngEx.what());
		}
		break;

	case(5):
		str = static_cast<uint8_t*>(executingProcess->_memoryManager->Virtual_To_Physical(executingProcess->m_registers[3]));
		length = *str;

		for (uint8_t charNum = 1; charNum < length; charNum++)
		{
			std::cout << str[charNum];
		}
		break;

	case(6):
		std::cin >> input;

		heapStrPtr = static_cast<uint8_t*>(executingProcess->_memoryManager->HeapAllocate(input.length() + 1, 1));

		executingProcess->m_registers[21] = executingProcess->_memoryManager->Physical_To_Virtual(VMFramework::PointerMath::Subtract(heapStrPtr, input.length() + 2));

		std::memcpy(heapStrPtr, input.c_str(), input.length() + 1);

		executingProcess->m_registers[3] = executingProcess->_memoryManager->Physical_To_Virtual(heapStrPtr);
		break;

	case(7):
		cstrPtr = static_cast<char*>(executingProcess->_memoryManager->Virtual_To_Physical(executingProcess->m_registers[3]));

		strLength = std::strlen(cstrPtr);

		if (strLength < std::numeric_limits<uint8_t>::min() || strLength > std::numeric_limits<uint8_t>::max())
			throw std::runtime_error("Machine only supports pascal strings with 255 characters or less");

		heapStrPtr = static_cast<uint8_t*>(executingProcess->_memoryManager->HeapAllocate(strLength + 1, 1));

		executingProcess->m_registers[21] = executingProcess->_memoryManager->Physical_To_Virtual(VMFramework::PointerMath::Subtract(heapStrPtr, strLength + 2));

		*heapStrPtr = static_cast<uint8_t>(strLength);

		std::memcpy(heapStrPtr + 1, cstrPtr, strLength);

		executingProcess->m_registers[3] = executingProcess->_memoryManager->Physical_To_Virtual(heapStrPtr);
		break;

	case(99):
		std::cout << "BRKPT reached. Press Enter to continue...";
		
		// Clear input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Waits for the user to press Enter
		std::cin.get();

#if defined(_LINUX_TARGET) || defined(_MAC_TARGET)
		// Move the cursor up by one line
		std::cout << "\033[A";

		// Clear the line
		std::cout << "\033[K";
#endif //defined(_LINUX_TARGET) || defined(_MAC_TARGET)
		break;

	default:
		throw std::runtime_error("Invalid trap code detected: " + std::to_string(executingProcess->operandOne));
	}
}