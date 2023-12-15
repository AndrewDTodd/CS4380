#include "../../../include/Instructions/Arth/DIV.h"

#include "../../../include/Process_4380.h"

DIV::DIV(): Instruction(17)
{}

void DIV::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] /=
		executingProcess->m_registers[executingProcess->operandTwo];
}