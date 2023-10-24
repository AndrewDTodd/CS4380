#include "../include/Process_4380.h"

#include "../include/ISA_4380.h"

using namespace VMFramework;

Process_4380::Process_4380(void* initialPC, StackAllocator* processStack, uint8_t* programStart, uint8_t* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa) :
	Process<Process_4380, int32_t, int32_t, ISA_4380>(initialPC, processStack, programStart, codeSegmentStart, machineMutex, isa)
{
}