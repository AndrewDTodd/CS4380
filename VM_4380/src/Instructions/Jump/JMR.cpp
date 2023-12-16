#include "../../../include/Instructions/Jump/JMR.h"

#include "../../../include/Process_4380.h"

JMR::JMR() : Instruction(2)
{}

void JMR::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[16] = executingProcess->m_registers[executingProcess->operandOne];
}