#include "../../../include/Instructions/Arth/MUL.h"

#include "../../../include/Process_4380.h"

MUL::MUL() : Instruction(16)
{}

void MUL::Op(Process_4380* executingProcess)
{
	if (!(executingProcess->operandOne > 15 && executingProcess->operandOne < 22))
	{
		executingProcess->m_registers[executingProcess->operandOne] *= executingProcess->m_registers[executingProcess->operandTwo];
	}
	else
	{
#ifdef _DEBUG
		switch (executingProcess->operandOne)
		{
		case 16:
			throw VMFramework::protection_fault("MUL used to modify PC");
			break;

		case 17:
			throw VMFramework::protection_fault("MUL used to modify SL");
			break;

		case 18:
			throw VMFramework::protection_fault("MUL used to modify SB");
			break;

		case 19:
			throw VMFramework::protection_fault("MUL used to modify SP");
			break;

		case 20:
			throw VMFramework::protection_fault("MUL used to modify FP");
			break;

		case 21:
			throw VMFramework::protection_fault("MUL used to modify HP");
		}
#else
		throw VMFramework::protection_fault("Improper modification of reserved register");
#endif // _DEBUG
	}
}