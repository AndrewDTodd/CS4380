#include "../../../include/Instructions/Move/LDR_R.h"

#include <cstring>
#include <algorithm>

#include "../../../include/Process_4380.h"

LDR_R::LDR_R() : Instruction(23)
{}

void LDR_R::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	const uint8_t* _source = static_cast<uint8_t*>(executingProcess->_memoryManager->Virtual_To_Physical(executingProcess->m_registers[executingProcess->operandTwo]));
	if (_source < executingProcess->_programEnd)
	{
		if constexpr (is_little_endian)
		{
			std::memcpy(&executingProcess->m_registers[executingProcess->operandOne], _source, sizeof(int32_t));
		}
		else
		{
			int32_t value;
			std::memcpy(&value, _source, sizeof(int32_t));

			uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);

			std::reverse(bytePtr, bytePtr + sizeof(int32_t));

			executingProcess->m_registers[executingProcess->operandOne] = value;
		}
	}
	else
	{
		throw VMFramework::segmentation_fault("Tried to read from memory outside the program space");
	}
}