#ifndef PROCESS_4380_H
#define PROCESS_4380_H

#include "Process.h"

#include <cstdint>

#include "Instructions/Instructions.h"

using namespace VMFramework;

class Process_4380 : public VMFramework::Process<int32_t, int32_t>
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
private:
	int32_t opcode = 0;
	int32_t operandOne = 0;
	int32_t operandTwo = 0;

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
};
#endif //!PROCESS_4380_H
