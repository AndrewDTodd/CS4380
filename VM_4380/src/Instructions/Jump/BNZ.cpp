#include "../../../include/Instructions/Jump/BNZ.h"

#include "../../../include/Process_4380.h"

BNZ::BNZ() : Instruction(3)
{}

void BNZ::Op(Process_4380* executingProcess)
{
	if (executingProcess->m_registers[executingProcess->operandOne] != 0)
	{
		executingProcess->m_registers[16] = executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_programStart + executingProcess->operandTwo);
	}
}