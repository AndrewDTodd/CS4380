#include "../../../include/Instructions/Move/STR_R.h"

#include <cstring>
#include <algorithm>

#include "../../../include/Process_4380.h"

STR_R::STR_R() : Instruction(22)
{}

void STR_R::Op(Process_4380* executingProcess)
{
	uint8_t* _destination = const_cast<uint8_t*>(executingProcess->_programStart) + executingProcess->m_registers[executingProcess->operandTwo];
	if (_destination < executingProcess->_codeSegment)
	{
		if constexpr (is_little_endian)
		{
			std::memcpy(_destination, &executingProcess->m_registers[executingProcess->operandOne], sizeof(int32_t));
		}
		else
		{
			int32_t value = executingProcess->m_registers[executingProcess->operandOne];

			uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);

			std::reverse(bytePtr, bytePtr + sizeof(int32_t));

			std::memcpy(_destination, bytePtr, sizeof(int32_t));
		}
	}
	else
	{
		if (_destination < executingProcess->_programEnd)
			throw VMFramework::protection_fault("Tried to write to code segment of program space");
		else
			throw VMFramework::segmentation_fault("Tried to write to memory outside the program space");
	}
}