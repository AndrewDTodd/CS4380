#include "../include/Process_4380.h"

#include <cstring>
#include <stdexcept>
#include <iostream>

#include "../include/ISA_4380.h"

Process_4380::Process_4380(void* initialPC, StackAllocator* processStack, uint8_t* programStart, uint8_t* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa) :
	Process<Process_4380, int32_t, int32_t, ISA_4380>(initialPC, processStack, programStart, codeSegmentStart, machineMutex, isa)
{
}

//inline int32_t Process_4380::ReadLittleEndianInt32()
//{
//	int32_t value = *m_registers.PC;
//
//	value = (value & 0x000000FF) << 24 |
//			(value & 0x0000FF00) << 8  |
//			(value & 0x00FF0000) >> 8  |
//			(value & 0xFF000000) >> 24;
//
//
//}

inline void Process_4380::Fetch()
{
	//Fetch 12 byte block from program at the PC location
	FetchBlock block;
	std::memcpy(&block, m_registers.PC, sizeof(FetchBlock));

	opcode = block.opcode;
	operandOne = block.operandOne;
	operandTwo = block.operandTwo;
}

inline void Process_4380::Increment()
{
	//Increment the PC by 3 (3 * 4 bytes for int32_t, or 12 bytes)
	m_registers.PC += 3;
}

inline void Process_4380::Decode()
{
	////Reinterpret the ints as little-endian
	//opcode = (opcode & 0x000000FF) << 24 |
	//		 (opcode & 0x0000FF00) << 8  |
	//		 (opcode & 0x00FF0000) >> 8  |
	//		 (opcode & 0xFF000000) >> 24;

	//operandOne = (operandOne & 0x000000FF) << 24 |
	//			 (operandOne & 0x0000FF00) << 8	 |
	//			 (operandOne & 0x00FF0000) >> 8  |
	//			 (operandOne & 0xFF000000) >> 24;

	//operandTwo = (operandTwo & 0x000000FF) << 24 |
	//			 (operandTwo & 0x0000FF00) << 8  |
	//			 (operandTwo & 0x00FF0000) >> 8  |
	//			 (operandTwo & 0xFF000000) >> 24;

	try
	{
		_instruction = _ISA->operator[](opcode);
	}
	catch (const std::out_of_range& opCodeEx)
	{
		std::cerr << "Error: " << opCodeEx.what() << std::endl;

		Stop();
	}
}

inline void Process_4380::Execute()
{
	try
	{
		_instruction->Op(this);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;

		Stop();
	}
}