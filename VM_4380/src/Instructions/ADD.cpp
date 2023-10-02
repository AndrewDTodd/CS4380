#include "../../include/Instructions/ADD.h"

ADD::ADD(): opcode(13)
{}

void ADD::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] += 
		executingProcess->m_registers[executingProcess->operandTwo];
}