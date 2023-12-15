#include "../../../include/Instructions/Stack/PEEK.h"

#include "../../../include/Process_4380.h"

PEEK::PEEK() : Instruction(42)
{}

void PEEK::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->Peek(executingProcess->m_registers[executingProcess->operandOne]);
}