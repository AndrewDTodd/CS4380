#include "../../../include/Instructions/Move/LDB_L.h"

#include "../../../include/Process_4380.h"

LDB_L::LDB_L() : Instruction(12)
{}

void LDB_L::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	const uint8_t* _source = executingProcess->_programStart + executingProcess->operandTwo;
	if (_source < executingProcess->_programEnd)
	{
		//executingProcess->m_registers[executingProcess->operandOne] = 0;
		std::memcpy(reinterpret_cast<uint8_t*>(&executingProcess->m_registers[executingProcess->operandOne]), _source, sizeof(uint8_t));
	}
	else
	{
		throw VMFramework::segmentation_fault("Tried to read from memory outside the program space");
	}
}