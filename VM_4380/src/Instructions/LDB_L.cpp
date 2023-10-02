#include "../../include/Instructions/LDB_L.h"

LDB_L::LDB_L() : opcode(12)
{}

void LDB_L::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] =
		static_cast<int32_t>(executingProcess->_programSegment[executingProcess->operandTwo]);
}