#include "../../include/Instructions/MOV.h"

MOV::MOV() : opcode(7)
{}

void MOV::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->m_registers[executingProcess->operandTwo];
}