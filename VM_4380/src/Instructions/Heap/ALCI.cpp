#include "../../../include/Instructions/Heap/ALCI.h"

#include "../../../include/Process_4380.h"

ALCI::ALCI() : Instruction(35)
{}

void ALCI::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	executingProcess->m_registers[executingProcess->operandOne] = executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_memoryManager->HeapAllocate(executingProcess->operandTwo, sizeof(int32_t)));
}