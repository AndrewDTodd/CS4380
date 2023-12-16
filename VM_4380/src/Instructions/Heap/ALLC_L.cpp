#include "../../../include/Instructions/Heap/ALLC_L.h"

#include "../../../include/Process_4380.h"

ALLC_L::ALLC_L() : Instruction(36)
{}

void ALLC_L::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_memoryManager->HeapAllocate(executingProcess->operandTwo, sizeof(int32_t)));
}