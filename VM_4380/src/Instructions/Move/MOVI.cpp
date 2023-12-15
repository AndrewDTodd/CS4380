#include "../../../include/Instructions/Move/MOVI.h"

#include "../../../include/Process_4380.h"

MOVI::MOVI() : Instruction(31)
{}

void MOVI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->operandTwo;
}