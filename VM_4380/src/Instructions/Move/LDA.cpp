#include "../../../include/Instructions/Move/LDA.h"

#include "../../../include/Process_4380.h"

LDA::LDA() : Instruction(8)
{}

void LDA::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->operandTwo;
}