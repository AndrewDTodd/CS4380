#ifndef PROCESS_4380_H
#define PROCESS_4380_H

#include "Process.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include <gtest/gtest_prod.h>

#include "ISA_4380.h"

#include "Instructions/VM_Instructions.h"

#include "rootConfig.h"

class Process_4380 : public VMFramework::Process<Process_4380, int32_t, int32_t, ISA_4380>
{
	FRIEND_TEST(InstructionsTesting, Validate_ADD);
	friend ADD;
	FRIEND_TEST(InstructionsTesting, Validate_DIV);
	friend DIV;
	FRIEND_TEST(InstructionsTesting, Validate_JMP_L);
	friend JMP_L;
	FRIEND_TEST(InstructionsTesting, Validate_LDB_L);
	friend LDB_L;
	FRIEND_TEST(InstructionsTesting, Validate_LDR_L);
	friend LDR_L;
	FRIEND_TEST(InstructionsTesting, Validate_MOV);
	friend MOV;
	friend STB_L;
	friend STR_L;
	FRIEND_TEST(InstructionsTesting, Validate_MUL);
	friend MUL;
	FRIEND_TEST(InstructionsTesting, Validate_SUB);
	friend SUB;
	FRIEND_TEST(InstructionsTesting, Validate_TRP);
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

	VMFramework::Instruction<int32_t, int32_t, Process_4380>* _instruction = nullptr;

	/// <summary>
	/// Internal healper to read the 4 byte little-endian opcode, operandOne and operandTwo from the PC
	/// </summary>
	/// <returns></returns>
	//inline int32_t ReadLittleEndianInt32();

	/// <summary>
	/// Used to preform the fetch step of execution cycle
	/// </summary>
	FRIEND_TEST(Process_4380Testing, Validate_Fetch);
	inline void Fetch() override
	{
		//Fetch 12 byte block from program at the PC location
		FetchBlock block;
		std::memcpy(&block, m_registers.PC, sizeof(FetchBlock));

		opcode = block.opcode;
		operandOne = block.operandOne;
		operandTwo = block.operandTwo;
	}

	/// <summary>
	/// Used to preform the increment step of the execution cycle
	/// </summary>
	FRIEND_TEST(Process_4380Testing, Validate_Increment);
	inline void Increment() override
	{
		//Increment the PC by 3 (3 * 4 bytes for int32_t, or 12 bytes)
		m_registers.PC += 3;
	}

	/// <summary>
	/// Used to preform the decode step of execution cycle
	/// </summary>
	FRIEND_TEST(Process_4380Testing, Validate_Decode);
	inline void Decode() override
	{
		try
		{
			_instruction = _ISA->operator[](opcode);
		}
		catch (const std::out_of_range& opCodeEx)
		{
			RED_TERMINAL
				std::cerr << "Error: " << opCodeEx.what() << std::endl;
			RESET_TERMINAL

			Stop();
		}
	}

	/// <summary>
	/// Used to preform the execute step of the execution cycle
	/// </summary>
	FRIEND_TEST(Process_4380Testing, Validate_Execute);
	inline void Execute() override
	{
		try
		{
			_instruction->Op(this);
		}
		catch (const std::exception& ex)
		{
			RED_TERMINAL
				std::cerr << "Error: " << ex.what() << std::endl;
			RESET_TERMINAL

			Stop();
		}
	}

public:
	/// <summary>
	/// Create Process specifying where in the program it will begin execution
	/// </summary>
	/// <param name="initialPC">The address in the program to begin execution at</param>
	/// <param name="processStack">Pointer to the StackAllocator for this process</param>
	/// <param name="programStart">Pointer to the begining of the program in memory</param>
	/// <param name="machineMutex">The shared_mutex in the spawning Machine</param>
	/// <param name="isa">Pointer to the ISA instance to use</param>
	Process_4380(void* initialPC, VMFramework::StackAllocator* processStack, uint8_t* programStart, uint8_t* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa);
};
#endif //!PROCESS_4380_H
