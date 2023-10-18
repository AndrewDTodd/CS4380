#include "../../../include/Instructions/Move/LDB_L.h"

#include "../../include/Process_4380.h"

LDB_L::LDB_L() : Instruction(12)
{}

void LDB_L::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] =
		static_cast<int32_t>(*(static_cast<uint8_t*>(executingProcess->_programSegment) + executingProcess->operandTwo));
}