#include "../../../include/Instructions/Move/STB_L.h"

#include <cstring>

#include "../../../include/Process_4380.h"

STB_L::STB_L() : Instruction(11)
{}

void STB_L::Op(Process_4380* executingProcess)
{
	std::memcpy(static_cast<uint8_t*>(executingProcess->_programSegment) + executingProcess->operandTwo, &executingProcess->m_registers[executingProcess->operandOne], sizeof(uint8_t));
}