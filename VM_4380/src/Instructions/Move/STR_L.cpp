#include "../../../include/Instructions/Move/STR_L.h"

#include <cstring>

#include "../../../include/Process_4380.h"

STR_L::STR_L() : Instruction(9)
{}

void STR_L::Op(Process_4380* executingProcess)
{
	std::memcpy(static_cast<uint8_t*>(executingProcess->_programSegment) + executingProcess->operandTwo, &executingProcess->m_registers[executingProcess->operandOne], sizeof(int32_t));
}