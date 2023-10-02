#include "../../include/Instructions/JMP_L.h"

JMP_L::JMP_L() : opcode(1)
{}

void JMP_L::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers.PC =
		executingProcess->_programSegment + executingProcess->operandOne;
}