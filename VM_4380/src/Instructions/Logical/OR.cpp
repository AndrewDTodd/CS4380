#include "../../../include/Instructions/Logical/OR.h"

#include "../../../include/Process_4380.h"

OR::OR() : Instruction(19)
{}

void OR::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] =
		(executingProcess->m_registers[executingProcess->operandOne] != 0) || (executingProcess->m_registers[executingProcess->operandTwo] != 0);
}