#include "../../../include/Instructions/Arth/ADD.h"

#include "../../include/Process_4380.h"

ADD::ADD() : Instruction(13)
{
}

void ADD::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] += 
		executingProcess->m_registers[executingProcess->operandTwo];
}