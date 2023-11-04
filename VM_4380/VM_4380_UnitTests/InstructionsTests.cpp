#include <gtest/gtest.h>

#include "../include/Instructions/VM_Instructions.h"

#include <stdexcept>
#include <shared_mutex>
#include <cstdint>

#include <iostream>
#include <sstream>

#include "../include/Process_4380.h"
#include "../include/ISA_4380.h"
#include <StackAllocator.h>

using namespace VMFramework;

class VMInstructionsTesting : public ::testing::Test
{
protected:
	std::shared_mutex _mutex;

	ISA_4380 _isa;

	uint8_t _program[78] =
	{
		0x06, 0x00, 0x00, 0x00, 0x57, 0x65, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00,
		0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00,
		0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	MemoryManager* m_memoryManager;

	StackAllocator* _stack;

	Process_4380* _process;

	void SetUp() override
	{
		m_memoryManager = MemoryManager::GetInstance();
		m_memoryManager->StartUp();

		_stack = AllocateNewAllocator<StackAllocator>(100, this->m_memoryManager->m_systemAllocator);

		_process = new Process_4380(7 * sizeof(uint8_t), _stack, _program, &_program[6], &_program[77], _mutex, &_isa);
	}

	void TearDown() override
	{
		delete _process;
		m_memoryManager->ShutDown();
	}
};

//Arth **************************************************************************************************
TEST_F(VMInstructionsTesting, Validate_ADD)
{
	_process->m_registers[0] = 1;
	_process->m_registers[1] = 1;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](13)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 2);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](13)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](13)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](13)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](13)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](13)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](13)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_ADDI)
{
	_process->m_registers[0] = 1;

	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](14)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 2);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](14)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](14)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](14)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](14)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](14)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](14)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_DIV)
{
	_process->m_registers[0] = 25;
	_process->m_registers[1] = 5;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](17)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 5);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](17)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](17)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](17)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](17)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](17)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](17)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_DIVI)
{
	_process->m_registers[0] = 25;

	_process->operandOne = 0;
	_process->operandTwo = 5;

	_isa.operator[](34)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 5);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](34)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](34)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](34)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](34)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](34)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](34)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_MUL)
{
	_process->m_registers[0] = 5;
	_process->m_registers[1] = 5;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](16)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 25);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](16)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](16)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](16)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](16)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](16)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](16)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_MULI)
{
	_process->m_registers[0] = 5;

	_process->operandOne = 0;
	_process->operandTwo = 5;

	_isa.operator[](33)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 25);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](33)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](33)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](33)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](33)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](33)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](33)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_SUB)
{
	_process->m_registers[0] = 25;
	_process->m_registers[1] = 5;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](15)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 20);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](15)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](15)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](15)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](15)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](15)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](15)->Op(_process), VMFramework::protection_fault);
}
//*******************************************************************************************************

//Comp **************************************************************************************************
TEST_F(VMInstructionsTesting, Validate_CMP)
{
	_process->m_registers[0] = 25;
	_process->m_registers[1] = 25;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](20)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 0);

	_process->m_registers[0] = 25;
	_process->m_registers[1] = 20;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](20)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 1);

	_process->m_registers[0] = 20;
	_process->m_registers[1] = 25;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](20)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], -1);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](20)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](20)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](20)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](20)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](20)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](20)->Op(_process), VMFramework::protection_fault);
}

TEST_F(VMInstructionsTesting, Validate_CMPI)
{
	_process->m_registers[0] = 25;

	_process->operandOne = 0;
	_process->operandTwo = 25;

	_isa.operator[](32)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 0);

	_process->m_registers[0] = 25;

	_process->operandOne = 0;
	_process->operandTwo = 20;

	_isa.operator[](32)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 1);

	_process->m_registers[0] = 20;

	_process->operandOne = 0;
	_process->operandTwo = 25;

	_isa.operator[](32)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], -1);

	_process->operandOne = 16;
	ASSERT_THROW(_isa.operator[](32)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 17;
	ASSERT_THROW(_isa.operator[](32)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 18;
	ASSERT_THROW(_isa.operator[](32)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 19;
	ASSERT_THROW(_isa.operator[](32)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 20;
	ASSERT_THROW(_isa.operator[](32)->Op(_process), VMFramework::protection_fault);
	_process->operandOne = 21;
	ASSERT_THROW(_isa.operator[](32)->Op(_process), VMFramework::protection_fault);
}
//*******************************************************************************************************

//Jump **************************************************************************************************
TEST_F(VMInstructionsTesting, Validate_BGT)
{
	_process->m_registers[0] = 1;
	_process->operandOne = 0;
	_process->operandTwo = 0x12;

	_isa.operator[](4)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x12);

	_process->m_registers[0] = 0;
	_process->operandOne = 0;
	_process->operandTwo = 0x30;

	_isa.operator[](4)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x12);
}

TEST_F(VMInstructionsTesting, Validate_BLT)
{
	_process->m_registers[0] = -1;
	_process->operandOne = 0;
	_process->operandTwo = 0x12;

	_isa.operator[](5)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x12);

	_process->m_registers[0] = 0;
	_process->operandOne = 0;
	_process->operandTwo = 0x30;

	_isa.operator[](5)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x12);
}

TEST_F(VMInstructionsTesting, Validate_BNZ)
{
	_process->m_registers[0] = -1;
	_process->operandOne = 0;
	_process->operandTwo = 0x12;

	_isa.operator[](3)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x12);

	_process->m_registers[0] = 1;
	_process->operandOne = 0;
	_process->operandTwo = 0x30;

	_isa.operator[](3)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x30);

	_process->m_registers[0] = 0;
	_process->operandOne = 0;
	_process->operandTwo = 0x40;

	_isa.operator[](3)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x30);
}

TEST_F(VMInstructionsTesting, Validate_BRZ)
{
	_process->m_registers[0] = -1;
	_process->m_registers[16] = 0;
	_process->operandOne = 0;
	_process->operandTwo = 0x12;

	_isa.operator[](6)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0);

	_process->m_registers[0] = 1;
	_process->operandOne = 0;
	_process->operandTwo = 0x30;

	_isa.operator[](6)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0);

	_process->m_registers[0] = 0;
	_process->operandOne = 0;
	_process->operandTwo = 0x40;

	_isa.operator[](6)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x40);
}

TEST_F(VMInstructionsTesting, Validate_JMP_L)
{
	_process->operandOne = 0x12;
	_isa.operator[](1)->Op(_process);

	ASSERT_EQ(_process->m_registers[16], 0x12);
}

TEST_F(VMInstructionsTesting, Validate_JMR)
{
	_process->m_registers[0] = 0x12;
	_process->operandOne = 0;

	_isa.operator[](2)->Op(_process);

	ASSERT_EQ(_program + _process->m_registers[16], _program + 0x12);
}
//*******************************************************************************************************

//Move **************************************************************************************************
TEST_F(VMInstructionsTesting, Validate_LDA)
{
	_process->operandOne = 0;
	_process->operandTwo = 4;

	_isa.operator[](8)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 4);
}

TEST_F(VMInstructionsTesting, Validate_LDB_L)
{
	_process->operandOne = 0;
	_process->operandTwo = 4;

	_isa.operator[](12)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 0x57);
}

TEST_F(VMInstructionsTesting, Validate_LDB_R)
{
	_process->m_registers[1] = 4;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](25)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], 0x57);
}

TEST_F(VMInstructionsTesting, Validate_LDR_L)
{
	_process->operandOne = 0;
	_process->operandTwo = 4;

	_isa.operator[](10)->Op(_process);
	//As it is in program
	//0x57, 0x65, 0x01, 0x00,
	//Interpreted as little-endian 4 byte int
	//0x00016557
	ASSERT_EQ(_process->m_registers[0], 0x00016557);
}

TEST_F(VMInstructionsTesting, Validate_LDR_R)
{
	_process->m_registers[1] = 4;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](23)->Op(_process);
	//As it is in program
	//0x57, 0x65, 0x01, 0x00,
	//Interpreted as little-endian 4 byte int
	//0x00016557
	ASSERT_EQ(_process->m_registers[0], 0x00016557);
}

TEST_F(VMInstructionsTesting, Validate_MOV)
{
	_process->m_registers[0] = 125;
	_process->m_registers[1] = -125;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](7)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], -125);
}

TEST_F(VMInstructionsTesting, Validate_MOVI)
{
	_process->m_registers[0] = 125;
	_process->operandOne = 0;
	_process->operandTwo = -125;

	_isa.operator[](31)->Op(_process);

	ASSERT_EQ(_process->m_registers[0], -125);
}

TEST_F(VMInstructionsTesting, Validate_STB_L)
{
	_process->m_registers[0] = 0x70;
	_process->operandOne = 0;
	_process->operandTwo = 4;

	_isa.operator[](11)->Op(_process);

	ASSERT_EQ(_program[4], 0x70);
}

TEST_F(VMInstructionsTesting, Validate_STB_R)
{
	_process->m_registers[0] = 0x70;
	_process->m_registers[1] = 4;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](24)->Op(_process);

	ASSERT_EQ(_program[4], 0x70);
}

TEST_F(VMInstructionsTesting, Validate_STR_L)
{
	_process->m_registers[0] = 0x12345678;
	_process->operandOne = 0;
	_process->operandTwo = 0;

	_isa.operator[](9)->Op(_process);

	if constexpr (is_little_endian)
	{
		ASSERT_EQ(_program[0], 0x78);
		ASSERT_EQ(_program[1], 0x56);
		ASSERT_EQ(_program[2], 0x34);
		ASSERT_EQ(_program[3], 0x12);
	}
	else
	{
		ASSERT_EQ(_program[0], 0x12);
		ASSERT_EQ(_program[1], 0x34);
		ASSERT_EQ(_program[2], 0x56);
		ASSERT_EQ(_program[3], 0x78);
	}
}

TEST_F(VMInstructionsTesting, Validate_STR_R)
{
	_process->m_registers[0] = 0x12345678;
	_process->m_registers[1] = 0;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](22)->Op(_process);

	if constexpr (is_little_endian)
	{
		ASSERT_EQ(_program[0], 0x78);
		ASSERT_EQ(_program[1], 0x56);
		ASSERT_EQ(_program[2], 0x34);
		ASSERT_EQ(_program[3], 0x12);
	}
	else
	{
		ASSERT_EQ(_program[0], 0x12);
		ASSERT_EQ(_program[1], 0x34);
		ASSERT_EQ(_program[2], 0x56);
		ASSERT_EQ(_program[3], 0x78);
	}
}
//*******************************************************************************************************

//TRP ***************************************************************************************************
TEST_F(VMInstructionsTesting, Validate_TRP)
{
	//Case TRP 1 *****************************************
	_process->m_registers[3] = 12345;
	_process->operandOne = 1;

	std::streambuf* originalBuffer = std::cout.rdbuf();

	std::ostringstream capturedOutput;

	std::cout.rdbuf(capturedOutput.rdbuf());

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(capturedOutput.str(), "12345");

	capturedOutput.str("");
	//****************************************************

	//Case TRP 2 *****************************************
	std::string testInput = "0x12345678";
	std::stringstream testStream(testInput);

	std::streambuf* origCin = std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 2;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->m_registers[3], 0x12345678);
	std::cin.clear();

	testInput = "-0x12345678";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 2;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->m_registers[3], -0x12345678);
	std::cin.clear();

	testInput = "1193046";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 2;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->m_registers[3], 0x123456);
	std::cin.clear();

	testInput = "FAIL";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 2;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();

	testInput = "0xFFFFFFFFFF";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 2;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();

	testInput = "1099511627775";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 2;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();
	//****************************************************

	//Case TRP 3 *****************************************
	_process->m_registers[3] = 0x57;
	_process->operandOne = 3;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(capturedOutput.str(), "W");

	std::cout.rdbuf(originalBuffer);
	//****************************************************

	//Case TRP 4 *****************************************
	testInput = "0xFF";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->m_registers[3], 0xFF);
	std::cin.clear();

	testInput = "238";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->m_registers[3], 0xEE);
	std::cin.clear();

	testInput = "FAIL";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();

	testInput = "0xFFF";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();

	testInput = "4095";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();

	testInput = "-0xF";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();

	testInput = "-15";
	testStream.str(testInput);
	std::cin.rdbuf(testStream.rdbuf());

	_process->operandOne = 4;

	ASSERT_THROW(_isa.operator[](21)->Op(_process), std::runtime_error);
	std::cin.clear();
	//****************************************************

	//Case TRP 0 *****************************************
	_process->operandOne = 0;

	ASSERT_EQ(_process->_run, true);

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->_run, false);

	//Must set _process to nullptr here as calling TRP 0 will stop the process and call its destructor. Tear down also calls delete
	_process = nullptr;
	//****************************************************

	std::cin.rdbuf(origCin);
}
//*******************************************************************************************************