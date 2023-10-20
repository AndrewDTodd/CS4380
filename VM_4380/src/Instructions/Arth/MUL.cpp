#include "../../../include/Instructions/Arth/MUL.h"

#include "../../../include/Process_4380.h"

MUL::MUL() : Instruction(16)
{}

void MUL::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] *= executingProcess->m_registers[executingProcess->operandTwo];
}