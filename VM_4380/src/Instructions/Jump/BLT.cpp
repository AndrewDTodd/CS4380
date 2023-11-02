#include "../../../include/Instructions/Jump/BLT.h"

#include "../../../include/Process_4380.h"

BLT::BLT() : Instruction(5)
{}

void BLT::Op(Process_4380* executingProcess)
{
	if (executingProcess->m_registers[executingProcess->operandOne] < 0)
	{
		executingProcess->m_registers[16] = executingProcess->operandTwo;
	}
}