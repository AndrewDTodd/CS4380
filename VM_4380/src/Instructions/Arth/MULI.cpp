#include "../../../include/Instructions/Arth/MULI.h"

#include "../../../include/Process_4380.h"

MULI::MULI() : Instruction(33)
{}

void MULI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] *= executingProcess->operandTwo;
}