#include "../../../include/Instructions/Heap/ALLC_R.h"

#include "../../../include/Process_4380.h"

ALLC_R::ALLC_R() : Instruction(37)
{}

void ALLC_R::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	throw NotImplemented();
}