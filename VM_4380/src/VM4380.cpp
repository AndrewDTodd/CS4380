#include "../include/VM4380.h"

using namespace VMFramework;

void VM4380::SpawnProcess(void* initialPC)
{
	StackAllocator* processStack = AllocateNewAllocator<StackAllocator>(PROCESS_STACK_BYTES, this->m_memoryManager->m_systemAllocator);

	Process_4380* process = new Process_4380(initialPC, processStack, m_programSegment, m_codeSegment, VM4380::_sharedMutex, &m_ISA);

	std::thread processThread(&Process_4380::Run, process);

	m_processThreads.push_back(std::move(processThread));
	m_processes.push_back(std::move(process));
}