#include "../include/Process_4380.h"

#include "../include/ISA_4380.h"

using namespace VMFramework;

Process_4380::Process_4380(const int32_t& initialPC,
	const uint8_t* programStart, const uint8_t* codeSegmentStart, const uint8_t* programEnd,
	ISA_4380* isa, std::shared_mutex& machineMutex, VMFramework::MemoryManager* memoryManager,
	const size_t& stackBytes, void* stackStart) :
	Process<Process_4380, int32_t, ISA_4380>(initialPC, programStart, codeSegmentStart, programEnd, isa, machineMutex, memoryManager, stackBytes, stackStart)
{
}