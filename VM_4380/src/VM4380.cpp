#include "../include/VM4380.h"

void VM4380::SpawnProcess(void* initialPC)
{
	StackAllocator* processStack = AllocateNew<StackAllocator>(PROCESS_STACK_BYTES, this->m_memoryManager->m_systemAllocator);

	Process_4380* process = new Process_4380(initialPC, processStack, m_programSegment, m_codeSegment, VM4380::_sharedMutex, &m_ISA);

	this->m_processes.push_back(process);

	std::thread thread(&Process_4380::Run, process);

	//wait for the thread to finish (only good for single thread program)
	thread.join();
}