#ifndef PROCESS_4380_H
#define PROCESS_4380_H

#include "Process.h"

#include <cstdint>

#include "Instructions/Instructions.h"

using namespace VMFramework;

class ISA_4380;

class Process_4380 : public VMFramework::Process<Process_4380, int32_t, int32_t, ISA_4380>
{
	friend ADD;
	friend DIV;
	friend JMP_L;
	friend LDB_L;
	friend LDR_L;
	friend MOV;
	friend MUL;
	friend SUB;
	friend TRP;
protected:
	struct FetchBlock
	{
		int32_t opcode;
		int32_t operandOne;
		int32_t operandTwo;
	};

	int32_t opcode = 0;
	int32_t operandOne = 0;
	int32_t operandTwo = 0;

	Instruction<int32_t, int32_t, Process_4380>* _instruction = nullptr;

	/// <summary>
	/// Internal healper to read the 4 byte little-endian opcode, operandOne and operandTwo from the PC
	/// </summary>
	/// <returns></returns>
	//inline int32_t ReadLittleEndianInt32();

	/// <summary>
	/// Used to preform the fetch step of execution cycle
	/// </summary>
	inline void Fetch() override;

	/// <summary>
	/// Used to preform the increment step of the execution cycle
	/// </summary>
	inline void Increment() override;

	/// <summary>
	/// Used to preform the decode step of execution cycle
	/// </summary>
	inline void Decode() override;

	/// <summary>
	/// Used to preform the execute step of the execution cycle
	/// </summary>
	inline void Execute() override;

public:
	/// <summary>
	/// Create Process specifying where in the program it will begin execution
	/// </summary>
	/// <param name="initialPC">The address in the program to begin execution at</param>
	/// <param name="processStack">Pointer to the StackAllocator for this process</param>
	/// <param name="programStart">Pointer to the begining of the program in memory</param>
	/// <param name="machineMutex">The shared_mutex in the spawning Machine</param>
	/// <param name="isa">Pointer to the ISA instance to use</param>
	Process_4380(void* initialPC, StackAllocator* processStack, uint8_t* programStart, uint8_t* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa);
};
#endif //!PROCESS_4380_H
