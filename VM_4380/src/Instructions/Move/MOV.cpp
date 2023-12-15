#include "../../../include/Instructions/Move/MOV.h"

#include "../../../include/Process_4380.h"

MOV::MOV() : Instruction(7)
{}

void MOV::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->m_registers[executingProcess->operandTwo];
}