#ifndef PROCESS_4380_H
#define PROCESS_4380_H

#include "Process.h"
#include "Machine.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include <gtest/gtest_prod.h>

#include "ISA_4380.h"

#include "Instructions/VM_Instructions.h"

#include "rootConfig.h"

class Process_4380 : public VMFramework::Process<Process_4380, int32_t, ISA_4380>
{
protected:
	struct FetchBlock
	{
		int32_t opcode;
		int32_t operandOne;
		int32_t operandTwo;
	};

	int32_t opcode;
	int32_t operandOne;
	int32_t operandTwo;

	VMFramework::Instruction<int32_t, Process_4380>* _instruction = nullptr;

	/// <summary>
	/// Used to preform the fetch step of execution cycle
	/// </summary>
	FRIEND_TEST(Process_4380Testing, Validate_Fetch);
	inline void Fetch() override
	{
		const uint8_t* _nextInstruction = _programStart + m_registers[16];
		if (_nextInstruction >= _codeSegment && _nextInstruction <= _programEnd - sizeof(FetchBlock))
		{
			FetchBlock block;
			if constexpr (is_little_endian)
			{
				//Fetch 12 byte block from program at the PC location
				std::memcpy(&block, _nextInstruction, sizeof(FetchBlock));

				opcode = block.opcode;
				operandOne = block.operandOne;
				operandTwo = block.operandTwo;
			}
			else
			{
				for (size_t i = 0; i < sizeof(int32_t); i++)
				{
					reinterpret_cast<uint8_t*>(&block.opcode)[3 - i] = _nextInstruction[i];
					reinterpret_cast<uint8_t*>(&block.operandOne)[3 - i] = _nextInstruction[i + sizeof(int32_t)];
					reinterpret_cast<uint8_t*>(&block.operandTwo)[3 - i] = _nextInstruction[i + 2 * sizeof(int32_t)];
				}
			}
		}
		else
		{
			if (_nextInstruction < _codeSegment)
				throw VMFramework::segmentation_fault("The PC was set to fetch from the data segment");
			else
				throw VMFramework::segmentation_fault("The PC was set to fetch from outside the valid executable region of process memory");
		}
	}

	/// <summary>
	/// Used to preform the increment step of the execution cycle
	/// </summary>
	FRIEND_TEST(Process_4380Testing, Validate_Increment);
	inline void Increment() override
	{
		//Increment the PC by 12 (3 * 4 bytes for int32_t, or 12 bytes)
		m_registers[16] += sizeof(FetchBlock);
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
	/// <param name="initialPC">The offset in the program to begin execution at</param>
	/// <param name="processStack">Pointer to the StackAllocator for this process</param>
	/// <param name="programStart">Pointer to the begining of the program in memory</param>
	/// <param name="machineMutex">The shared_mutex in the spawning Machine</param>
	/// <param name="isa">Pointer to the ISA instance to use</param>
	Process_4380(const void* initialPC, 
		const uint8_t* programStart, const uint8_t* codeSegmentStart, const uint8_t* programEnd,
		ISA_4380* isa, std::shared_mutex& machineMutex, VMFramework::MemoryManager* memoryManager,
		const size_t& stackBytes, void* stackStart);

	//Arth ******************************************************************************
	FRIEND_TEST(VMInstructionsTesting, Validate_ADD);
	friend ADD;
	FRIEND_TEST(VMInstructionsTesting, Validate_ADDI);
	friend ADDI;
	FRIEND_TEST(VMInstructionsTesting, Validate_DIV);
	friend DIV;
	FRIEND_TEST(VMInstructionsTesting, Validate_DIVI);
	friend DIVI;
	FRIEND_TEST(VMInstructionsTesting, Validate_MUL);
	friend MUL;
	FRIEND_TEST(VMInstructionsTesting, Validate_MULI);
	friend MULI;
	FRIEND_TEST(VMInstructionsTesting, Validate_SUB);
	friend SUB;
	//************************************************************************************
	
	//Comp *******************************************************************************
	FRIEND_TEST(VMInstructionsTesting, Validate_CMP);
	friend CMP;
	FRIEND_TEST(VMInstructionsTesting, Validate_CMPI);
	friend CMPI;
	//************************************************************************************
	
	//Heap *******************************************************************************
	//************************************************************************************
	
	//Jump *******************************************************************************
	FRIEND_TEST(VMInstructionsTesting, Validate_BGT);
	friend BGT;
	FRIEND_TEST(VMInstructionsTesting, Validate_BLT);
	friend BLT;
	FRIEND_TEST(VMInstructionsTesting, Validate_BNZ);
	friend BNZ;
	FRIEND_TEST(VMInstructionsTesting, Validate_BRZ);
	friend BRZ;
	FRIEND_TEST(VMInstructionsTesting, Validate_JMP_L);
	friend JMP_L;
	FRIEND_TEST(VMInstructionsTesting, Validate_JMR);
	friend JMR;
	//************************************************************************************
	
	//Logical ****************************************************************************
	//************************************************************************************
	
	//Move *******************************************************************************
	FRIEND_TEST(VMInstructionsTesting, Validate_LDA);
	friend LDA;
	FRIEND_TEST(VMInstructionsTesting, Validate_LDB_L);
	friend LDB_L;
	FRIEND_TEST(VMInstructionsTesting, Validate_LDB_R);
	friend LDB_R;
	FRIEND_TEST(VMInstructionsTesting, Validate_LDR_L);
	friend LDR_L;
	FRIEND_TEST(VMInstructionsTesting, Validate_LDR_R);
	friend LDR_R;
	FRIEND_TEST(VMInstructionsTesting, Validate_MOV);
	friend MOV;
	FRIEND_TEST(VMInstructionsTesting, Validate_MOVI);
	friend MOVI;
	FRIEND_TEST(VMInstructionsTesting, Validate_STB_L);
	friend STB_L;
	FRIEND_TEST(VMInstructionsTesting, Validate_STB_R);
	friend STB_R;
	FRIEND_TEST(VMInstructionsTesting, Validate_STR_L);
	friend STR_L;
	FRIEND_TEST(VMInstructionsTesting, Validate_STR_R);
	friend STR_R;
	//************************************************************************************
	
	//Multi-Thread ***********************************************************************
	//************************************************************************************
	
	//TRP ********************************************************************************
	FRIEND_TEST(VMInstructionsTesting, Validate_TRP);
	friend TRP;
	//************************************************************************************
};
#endif //!PROCESS_4380_H
