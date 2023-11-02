#include "../../../include/Instructions/Jump/JMP_L.h"

#include "../../../include/Process_4380.h"

JMP_L::JMP_L() : Instruction(1)
{}

void JMP_L::Op(Process_4380* executingProcess)
{
	executingProcess->m_registers[16] = executingProcess->operandOne;
}