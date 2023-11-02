#include "../include/Process_4380.h"

#include "../include/ISA_4380.h"

using namespace VMFramework;

Process_4380::Process_4380(const int32_t& initialPC, StackAllocator* processStack, 
	const uint8_t* programStart, const uint8_t* codeSegmentStart, const uint8_t* programEnd,
	std::shared_mutex& machineMutex, ISA_4380* isa) :
	Process<Process_4380, int32_t, ISA_4380>(initialPC, processStack, programStart, codeSegmentStart, programEnd, machineMutex, isa)
{
}