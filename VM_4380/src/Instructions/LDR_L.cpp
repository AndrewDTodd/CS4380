#include "../../include/Instructions/LDR_L.h"

LDR_L::LDR_L() : opcode(10)
{}

void LDB_L::Op(Process_4380* executingProcess)
{
	const uint8_t* startOfInt = executingProcess->_programSegment + executingProcess->operandTwo;

	executingProcess->m_registers[executingProcess->operandOne] =
		*reinterpret_cast<const int32_t*>(startOfInt);
}