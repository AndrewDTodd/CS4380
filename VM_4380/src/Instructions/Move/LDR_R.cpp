#include "../../../include/Instructions/Move/LDR_R.h"

#include <cstring>
#include <algorithm>

#include "../../../include/Process_4380.h"

LDR_R::LDR_R() : Instruction(23)
{}

void LDR_R::Op(Process_4380* executingProcess)
{
	if (!(executingProcess->operandOne > 15 && executingProcess->operandOne < 22))
	{
		const uint8_t* _source = const_cast<const uint8_t*>(executingProcess->_programStart) + executingProcess->m_registers[executingProcess->operandTwo];
		if (_source < executingProcess->_programEnd)
		{
			if constexpr (is_little_endian)
			{
				std::memcpy(&executingProcess->m_registers[executingProcess->operandOne], _source, sizeof(int32_t));
			}
			else
			{
				int32_t value;
				std::memcpy(&value, _source, sizeof(int32_t));

				uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);

				std::reverse(bytePtr, bytePtr + sizeof(int32_t));

				executingProcess->m_registers[executingProcess->operandOne] = value;
			}
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
			throw VMFramework::protection_fault("LDR used to modify PC");
			break;

		case 17:
			throw VMFramework::protection_fault("LDR used to modify SL");
			break;

		case 18:
			throw VMFramework::protection_fault("LDR used to modify SB");
			break;

		case 19:
			throw VMFramework::protection_fault("LDR used to modify SP");
			break;

		case 20:
			throw VMFramework::protection_fault("LDR used to modify FP");
			break;

		case 21:
			throw VMFramework::protection_fault("LDR used to modify HP");
		}
#else
		throw VMFramework::protection_fault("Improper modification of reserved register");
#endif // _DEBUG
	}
}