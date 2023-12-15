#include "../../../include/Instructions/Comp/CMPI.h"

#include "../../../include/Process_4380.h"

CMPI::CMPI() : Instruction(32)
{}

void CMPI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	int32_t& registerOne = executingProcess->m_registers[executingProcess->operandOne];
	int32_t& immediate = executingProcess->operandTwo;

	if (registerOne == immediate)
	{
		registerOne = 0;
	}
	else if (registerOne > immediate)
	{
		registerOne = 1;
	}
	else
	{
		registerOne = -1;
	}
}