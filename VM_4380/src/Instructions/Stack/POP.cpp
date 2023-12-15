#include "../../../include/Instructions/Stack/POP.h"

#include "../../../include/Process_4380.h"

POP::POP() : Instruction(41)
{}

void POP::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->Pop(executingProcess->m_registers[executingProcess->operandOne]);
}