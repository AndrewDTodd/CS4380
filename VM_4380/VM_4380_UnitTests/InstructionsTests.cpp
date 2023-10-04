#include <gtest/gtest.h>

#include "../include/Instructions/Instructions.h"

#include <stdexcept>
#include <shared_mutex>
#include <cstdint>

#include <iostream>
#include <sstream>

#include "../include/Process_4380.h"
#include "../include/ISA_4380.h"
#include "../../VMFramework/include/StackAllocator.h"

using namespace VMFramework;

class InstructionsTesting : public ::testing::Test
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

		_process = new Process_4380(&_program[6], _stack, _program, &_program[6], _mutex, &_isa);
	}

	void TearDown() override
	{
		delete _process;
		m_memoryManager->ShutDown();
	}
};

TEST_F(InstructionsTesting, Validate_ADD)
{
	_process->m_registers.gpRegisters[0] = 1;
	_process->m_registers.gpRegisters[1] = 1;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](13)->Op(_process);

	ASSERT_EQ(_process->m_registers.gpRegisters[0], 2);
}

TEST_F(InstructionsTesting, Validate_DIV)
{
	_process->m_registers.gpRegisters[0] = 25;
	_process->m_registers.gpRegisters[1] = 5;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](17)->Op(_process);

	ASSERT_EQ(_process->m_registers.gpRegisters[0], 5);
}

TEST_F(InstructionsTesting, Validate_JMP_L)
{
	_process->operandOne = 0x12;

	_isa.operator[](1)->Op(_process);

	ASSERT_EQ(_process->m_registers.PC, reinterpret_cast<int32_t*>(_program + 0x12));
}

TEST_F(InstructionsTesting, Validate_LDB_L)
{
	_process->operandOne = 0;
	_process->operandTwo = 4;

	_isa.operator[](12)->Op(_process);

	ASSERT_EQ(_process->m_registers.gpRegisters[0], 0x57);
}

TEST_F(InstructionsTesting, Validate_LDR_L)
{
	_process->operandOne = 0;
	_process->operandTwo = 4;

	_isa.operator[](10)->Op(_process);
	//As it is in program
	//0x57, 0x65, 0x01, 0x00,
	//Interpreted to little-endian 4 byte int
	//0x00016557
	ASSERT_EQ(_process->m_registers.gpRegisters[0], 0x00016557);
}

TEST_F(InstructionsTesting, Validate_MOV)
{
	_process->m_registers.gpRegisters[0] = 125;
	_process->m_registers.gpRegisters[1] = -125;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](7)->Op(_process);
	
	ASSERT_EQ(_process->m_registers.gpRegisters[0], -125);
}

TEST_F(InstructionsTesting, Validate_MUL)
{
	_process->m_registers.gpRegisters[0] = 5;
	_process->m_registers.gpRegisters[1] = 5;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](16)->Op(_process);
	
	ASSERT_EQ(_process->m_registers.gpRegisters[0], 25);
}

TEST_F(InstructionsTesting, Validate_SUB)
{
	_process->m_registers.gpRegisters[0] = 25;
	_process->m_registers.gpRegisters[1] = 5;
	_process->operandOne = 0;
	_process->operandTwo = 1;

	_isa.operator[](15)->Op(_process);
	
	ASSERT_EQ(_process->m_registers.gpRegisters[0], 20);
}

TEST_F(InstructionsTesting, Validate_TRP)
{
	_process->m_registers.gpRegisters[3] = 12345;
	_process->operandOne = 1;

	std::streambuf* originalBuffer = std::cout.rdbuf();

	std::ostringstream capturedOutput;

	std::cout.rdbuf(capturedOutput.rdbuf());

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(capturedOutput.str(), "12345");

	capturedOutput.str("");

	_process->m_registers.gpRegisters[3] = 0x57;
	_process->operandOne = 3;

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(capturedOutput.str(), "W");

	std::cout.rdbuf(originalBuffer);

	_process->operandOne = 0;

	ASSERT_EQ(_process->_run, true);

	_isa.operator[](21)->Op(_process);

	ASSERT_EQ(_process->_run, false);

	//Must set _process to nullptr here as calling TRP 0 will stop the process and call its destructor. Tear down also calls delete
	_process = nullptr;
}