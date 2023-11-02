#include "../../../include/Instructions/Comp/CMPI.h"

#include "../../../include/Process_4380.h"

CMPI::CMPI() : Instruction(32)
{}

void CMPI::Op(Process_4380* executingProcess)
{
	if (!(executingProcess->operandOne > 15 && executingProcess->operandOne < 22))
	{
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
	else
	{
#ifdef _DEBUG
		switch (executingProcess->operandOne)
		{
		case 16:
			throw VMFramework::protection_fault("CMPI used to modify PC");
			break;

		case 17:
			throw VMFramework::protection_fault("CMPI used to modify SL");
			break;

		case 18:
			throw VMFramework::protection_fault("CMPI used to modify SB");
			break;

		case 19:
			throw VMFramework::protection_fault("CMPI used to modify SP");
			break;

		case 20:
			throw VMFramework::protection_fault("CMPI used to modify FP");
			break;

		case 21:
			throw VMFramework::protection_fault("CMPI used to modify HP");
		}
#else
		throw VMFramework::protection_fault("Improper modification of reserved register");
#endif // _DEBUG
	}
}