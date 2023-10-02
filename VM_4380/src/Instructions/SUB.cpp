#include "../../include/Instructions/SUB.h"

SUB::SUB() : opcode(15)
{}

void SUB::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] -= executingProcess->m_registers[executingProcess->operandTwo];
}