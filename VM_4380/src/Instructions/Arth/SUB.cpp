#include "../../../include/Instructions/Arth/SUB.h"

#include "../../../include/Process_4380.h"

SUB::SUB() : Instruction(15)
{}

void SUB::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] -= executingProcess->m_registers[executingProcess->operandTwo];
}