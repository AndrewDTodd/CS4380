#include "../../../include/Instructions/Arth/ADDI.h"

#include "../../../include/Process_4380.h"

ADDI::ADDI() : Instruction(14)
{
}

void ADDI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] += executingProcess->operandTwo;
}