#include "../../../include/Instructions/Arth/SUB.h"

#include "../../../include/Process_4380.h"

SUB::SUB() : Instruction(15)
{}

void SUB::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] -= executingProcess->m_registers[executingProcess->operandTwo];
}