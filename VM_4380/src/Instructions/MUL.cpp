#include "../../include/Instructions/MUL.h"

MUL::MUL() : opcode(16)
{}

void MUL::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] *= executingProcess->m_registers[executingProcess->operandTwo];
}