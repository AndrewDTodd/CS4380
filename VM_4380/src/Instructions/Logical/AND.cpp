#include "../../../include/Instructions/Logical/AND.h"

#include "../../../include/Process_4380.h"

AND::AND() : Instruction(18)
{}

void AND::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] =
		(executingProcess->m_registers[executingProcess->operandOne] != 0) && (executingProcess->m_registers[executingProcess->operandTwo] != 0);
}