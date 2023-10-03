#include "../../include/Instructions/LDR_L.h"

#include <cstring>

#include "../../include/Process_4380.h"

LDR_L::LDR_L() : Instruction(10)
{}

void LDR_L::Op(Process_4380* executingProcess)
{
	std::memcpy(&executingProcess->m_registers[executingProcess->operandOne], static_cast<uint8_t*>(executingProcess->_programSegment) + executingProcess->operandTwo, sizeof(int32_t));
}