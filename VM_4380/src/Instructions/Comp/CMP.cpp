#include "../../../include/Instructions/Comp/CMP.h"

#include "../../../include/Process_4380.h"

CMP::CMP() : Instruction(20)
{}

void CMP::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	int32_t& registerOne = executingProcess->m_registers[executingProcess->operandOne];
	int32_t& registerTwo = executingProcess->m_registers[executingProcess->operandTwo];

	if (registerOne == registerTwo)
	{
		registerOne = 0;
	}
	else if (registerOne > registerTwo)
	{
		registerOne = 1;
	}
	else
	{
		registerOne = -1;
	}
}