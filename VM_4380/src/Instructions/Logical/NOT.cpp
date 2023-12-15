#include "../../../include/Instructions/Logical/NOT.h"

#include "../../../include/Process_4380.h"

NOT::NOT() : Instruction(39)
{}

void NOT::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] =
		!((executingProcess->m_registers[executingProcess->operandOne] != 0) || (executingProcess->m_registers[executingProcess->operandTwo] != 0));
}