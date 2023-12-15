#include "../../../include/Instructions/Jump/BAL_L.h"

#include "../../../include/Process_4380.h"

BAL_L::BAL_L() : Instruction(43)
{}

void BAL_L::Op(Process_4380* executingProcess)
{
	executingProcess->AdvanceAndLink();

	executingProcess->m_registers[16] =
		executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_programStart + executingProcess->operandOne);
}