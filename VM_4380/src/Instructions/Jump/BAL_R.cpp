#include "../../../include/Instructions/Jump/BAL_R.h"

#include "../../../include/Process_4380.h"

BAL_R::BAL_R() : Instruction(44)
{}

void BAL_R::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->AdvanceFrame();

	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->m_registers[16];

	executingProcess->m_registers[16] =
		executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_programStart + executingProcess->operandTwo);
}