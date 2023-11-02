#include "../../../include/Instructions/Jump/BGT.h"

#include "../../../include/Process_4380.h"

BGT::BGT() : Instruction(4)
{}

void BGT::Op(Process_4380* executingProcess)
{
	if (executingProcess->m_registers[executingProcess->operandOne] > 0)
	{
		executingProcess->m_registers[16] = executingProcess->operandTwo;
	}
}