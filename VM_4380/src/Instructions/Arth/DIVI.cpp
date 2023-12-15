#include "../../../include/Instructions/Arth/DIVI.h"

#include "../../../include/Process_4380.h"

DIVI::DIVI() : Instruction(34)
{}

void DIVI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] /= executingProcess->operandTwo;
}