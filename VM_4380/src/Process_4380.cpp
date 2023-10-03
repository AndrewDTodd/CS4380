#include "../include/Process_4380.h"

#include "../include/ISA_4380.h"

Process_4380::Process_4380(void* initialPC, StackAllocator* processStack, void* programStart, void* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa) :
	Process<Process_4380, int32_t, int32_t, ISA_4380>(initialPC, processStack, programStart, codeSegmentStart, machineMutex, isa)
{
}

inline void Process_4380::Fetch()
{

}

inline void Process_4380::Increment()
{

}

inline void Process_4380::Decode()
{

}

inline void Process_4380::Execute()
{

}