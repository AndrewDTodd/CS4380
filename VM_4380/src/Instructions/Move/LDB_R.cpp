#include "../../../include/Instructions/Move/LDB_R.h"

#include "../../../include/Process_4380.h"

LDB_R::LDB_R() : Instruction(25)
{}

void LDB_R::Op(Process_4380* executingProcess)
{
	if (!(executingProcess->operandOne > 15 && executingProcess->operandOne < 22))
	{
		const uint8_t* _source = const_cast<const uint8_t*>(executingProcess->_programStart) + executingProcess->m_registers[executingProcess->operandTwo];
		if (_source < executingProcess->_programEnd)
		{
			std::memcpy(reinterpret_cast<uint8_t*>(&executingProcess->m_registers[executingProcess->operandOne]), _source, sizeof(uint8_t));
		}
		else
		{
			throw VMFramework::segmentation_fault("Tried to read from memory outside the program space");
		}
	}
	else
	{
#ifdef _DEBUG
		switch (executingProcess->operandOne)
		{
		case 16:
			throw VMFramework::protection_fault("LDB used to modify PC");
			break;

		case 17:
			throw VMFramework::protection_fault("LDB used to modify SL");
			break;

		case 18:
			throw VMFramework::protection_fault("LDB used to modify SB");
			break;

		case 19:
			throw VMFramework::protection_fault("LDB used to modify SP");
			break;

		case 20:
			throw VMFramework::protection_fault("LDB used to modify FP");
			break;

		case 21:
			throw VMFramework::protection_fault("LDB used to modify HP");
		}
#else
		throw VMFramework::protection_fault("Improper modification of reserved register");
#endif // _DEBUG
	}
}