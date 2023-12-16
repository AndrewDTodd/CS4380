#include "../../../include/Instructions/Heap/ALLC_R.h"

#include "../../../include/Process_4380.h"

ALLC_R::ALLC_R() : Instruction(37)
{}

void ALLC_R::Op(Process_4380* executingProcess)
{
	executingProcess->CheckRegisterIDInvalid<16, 17, 18>(executingProcess->operandOne);

	int32_t* bytesToAllocatePtr = static_cast<int32_t*>(executingProcess->_memoryManager->Virtual_To_Physical(executingProcess->m_registers[executingProcess->operandTwo]));

	executingProcess->m_registers[executingProcess->operandOne] = 
		executingProcess->_memoryManager->Physical_To_Virtual(executingProcess->_memoryManager->HeapAllocate(*bytesToAllocatePtr, sizeof(int32_t)));
}