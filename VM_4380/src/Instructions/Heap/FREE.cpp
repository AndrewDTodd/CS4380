#include "../../../include/Instructions/Heap/FREE.h"

#include "../../../include/Process_4380.h"

FREE::FREE() : Instruction(38)
{}

void FREE::Op(Process_4380* executingProcess)
{
	void* ptrToHeapAlloc = executingProcess->_memoryManager->Virtual_To_Physical(executingProcess->m_registers[executingProcess->operandOne]);

	executingProcess->_memoryManager->HeapFree(ptrToHeapAlloc);
}