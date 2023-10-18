#include "../../../include/Instructions/Move/MOV.h"

#include "../../include/Process_4380.h"

MOV::MOV() : Instruction(7)
{}

void MOV::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->m_registers[executingProcess->operandTwo];
}