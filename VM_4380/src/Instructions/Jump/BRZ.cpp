#include "../../../include/Instructions/Jump/BRZ.h"

#include "../../../include/Process_4380.h"

BRZ::BRZ() : Instruction(6)
{}

void BRZ::Op(Process_4380* executingProcess)
{
	if (executingProcess->m_registers[executingProcess->operandOne] == 0)
	{
		executingProcess->m_registers[16] = executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_programStart + executingProcess->operandTwo);
	}
}