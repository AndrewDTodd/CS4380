#include "../../../include/Instructions/Multi_Thread/RUN.h"

#include "../../../include/Process_4380.h"

RUN::RUN() : Instruction(26)
{}

void RUN::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	throw NotImplemented();
}