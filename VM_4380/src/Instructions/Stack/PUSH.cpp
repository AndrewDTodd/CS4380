#include "../../../include/Instructions/Stack/PUSH.h"

#include "../../../include/Process_4380.h"

PUSH::PUSH() : Instruction(40)
{}

void PUSH::Op(Process_4380* executingProcess)
{
	executingProcess->Push(executingProcess->m_registers[executingProcess->operandOne]);
}