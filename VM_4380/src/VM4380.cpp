#include "../include/VM4380.h"

#include <stdexcept>

using namespace VMFramework;

void VM4380::SpawnProcess(const int32_t& initialPC)
{
	StackAllocator* processStack = AllocateNewAllocator<StackAllocator>(PROCESS_STACK_BYTES, this->m_memoryManager->m_systemAllocator);

	try
	{
		Process_4380* process = new Process_4380(initialPC, processStack,
			m_programSegment, m_codeSegment, (m_programSegment + m_programSize),
			VM4380::_sharedMutex, &m_ISA);

		std::thread processThread(&Process_4380::Run, process);

		m_processThreads.push_back(std::move(processThread));
		m_processes.push_back(std::move(process));
	}
	catch (const std::runtime_error& rntEx)
	{
		RED_TERMINAL
			std::cerr << "Error when spawning process: " << rntEx.what() << std::endl;
		RESET_TERMINAL

		//Free this process stack from the system's resources
		DeallocateDelete<StackAllocator>(*MemoryManager::GetInstance()->m_systemAllocator, *processStack);
	}
}

int32_t VM4380::CalculatePrimaryThreadInitPC()
{
	int32_t offset;
	if constexpr (is_little_endian)
	{
		offset = *reinterpret_cast<const int32_t*>(m_programSegment);
	}
	else
	{
		//This is only applicable if system is big-endian
		//Get the offset to the initial PC from the first 4 bytes in program
		//!!REMEMBER, the file is in LITTLE-ENDIAN!!!:(
		offset = static_cast<int32_t>(m_programSegment[0]);
		offset |= static_cast<int32_t>(m_programSegment[1]) << 8;
		offset |= static_cast<int32_t>(m_programSegment[2]) << 16;
		offset |= static_cast<int32_t>(m_programSegment[3]) << 24;
	}

	if (offset < 0 || offset >= m_programSize)
		throw std::runtime_error("Offset to initial PC at begining of program is invalid. Offset is to byte " + std::to_string(offset) + ". Program size is " + std::to_string(m_programSize) + " bytes.");

	return offset;
}