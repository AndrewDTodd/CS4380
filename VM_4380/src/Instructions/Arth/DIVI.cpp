#include "../../../include/Instructions/Arth/DIVI.h"

#include "../../../include/Process_4380.h"

DIVI::DIVI() : Instruction(34)
{}

void DIVI::Op(Process_4380* executingProcess)
{
	if (!(executingProcess->operandOne > 15 && executingProcess->operandOne < 22))
	{
		executingProcess->m_registers[executingProcess->operandOne] /= executingProcess->operandTwo;
	}
	else
	{
#ifdef _DEBUG
		switch (executingProcess->operandOne)
		{
		case 16:
			throw VMFramework::protection_fault("DIVI used to modify PC");
			break;

		case 17:
			throw VMFramework::protection_fault("DIVI used to modify SL");
			break;

		case 18:
			throw VMFramework::protection_fault("DIVI used to modify SB");
			break;

		case 19:
			throw VMFramework::protection_fault("DIVI used to modify SP");
			break;

		case 20:
			throw VMFramework::protection_fault("DIVI used to modify FP");
			break;

		case 21:
			throw VMFramework::protection_fault("DIVI used to modify HP");
		}
#else
		throw VMFramework::protection_fault("Improper modification of reserved register");
#endif // _DEBUG
	}
}