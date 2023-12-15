#include "../../../include/Instructions/Heap/ALCI.h"

#include "../../../include/Process_4380.h"

ALCI::ALCI() : Instruction(35)
{}

void ALCI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	throw NotImplemented();
}