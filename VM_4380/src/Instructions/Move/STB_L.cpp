#include "../../../include/Instructions/Move/STB_L.h"

#include <cstring>

#include "../../../include/Process_4380.h"

STB_L::STB_L() : Instruction(11)
{}

void STB_L::Op(Process_4380* executingProcess)
{
	uint8_t* _destination = const_cast<uint8_t*>(executingProcess->_programStart) + executingProcess->operandTwo;
	if (_destination < executingProcess->_codeSegment)
	{
		if constexpr (is_little_endian)
		{
			std::memcpy(_destination, &executingProcess->m_registers[executingProcess->operandOne], sizeof(uint8_t));
		}
		else
		{
			uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&executingProcess->m_registers[executingProcess->operandOne]);

			std::memcpy(_destination, bytePtr + sizeof(int32_t) - 1, sizeof(uint8_t));
		}
	}
	else
	{
		throw VMFramework::protection_fault("Tried to write to code segment of program space");
	}
}