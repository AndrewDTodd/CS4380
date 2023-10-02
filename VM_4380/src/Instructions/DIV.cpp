#include "../../include/Instructions/DIV.h"

DIV::DIV(): opcode(17)
{}

void DIV::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] /=
		executingProcess->m_registers[executingProcess->operandTwo];
}