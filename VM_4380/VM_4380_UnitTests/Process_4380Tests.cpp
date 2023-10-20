#include <gtest/gtest.h>

#include <stdexcept>
#include <shared_mutex>
#include <cstdint>

#include "../include/Instructions/Instructions.h"

#include "../include/Process_4380.h"
#include "../include/ISA_4380.h"
#include <StackAllocator.h>

using namespace VMFramework;

class Process_4380Testing : public ::testing::Test
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

	void* _memory = malloc(100);

	StackAllocator* _stack = new (_memory) StackAllocator(100, VMFramework::PointerMath::Add(_memory, sizeof(StackAllocator)));

	void SetUp() override
	{

	}

	void TearDown() override
	{
		_stack->~StackAllocator();
		free(_memory);
	}
};

//Process_4380(void* initialPC, StackAllocator* processStack, uint8_t* programStart, uint8_t* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa);
TEST_F(Process_4380Testing, Validate_ConstructorValidInput)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _stack, _program, &_program[6], _mutex, &_isa); });
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnNullPC)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(nullptr, _stack, _program, &_program[6], _mutex, &_isa);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnNullProgramPointer)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], _stack, nullptr, &_program[6], _mutex, &_isa);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnNullCodeSegmentPointer)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], _stack, _program, nullptr, _mutex, &_isa);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnInvalidCodeStart)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], _stack, _program, _program - 1, _mutex, &_isa);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnPCInDataSegment)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(_program, _stack, _program, &_program[6], _mutex, &_isa); }, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnInvalidPC)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(_program - 1, _stack, _program, &_program[6], _mutex, &_isa); }, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_Fetch)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _stack, _program, &_program[6], _mutex, &_isa); });

	_process->Fetch();

	//validate the opcode is now 0x01
	EXPECT_EQ(_process->opcode, 0x01);

	//Validate the operandOne is now 0x12
	EXPECT_EQ(_process->operandOne, 0x12);

	//Validate the operandTwo is now 0x00
	EXPECT_EQ(_process->operandTwo, 0x00);
}

TEST_F(Process_4380Testing, Validate_Increment)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _stack, _program, &_program[6], _mutex, &_isa); });

	_process->Increment();

	ASSERT_EQ(_process->m_registers.PC, reinterpret_cast<int32_t*>(_program + 18));
}

TEST_F(Process_4380Testing, Validate_Decode)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _stack, _program, &_program[6], _mutex, &_isa); });

	_process->opcode = 1;

	_process->Decode();

	ASSERT_EQ(typeid(*_process->_instruction), typeid(JMP_L));

	_process->opcode = 21;

	_process->Decode();

	ASSERT_EQ(typeid(*_process->_instruction), typeid(TRP));
}

TEST_F(Process_4380Testing, Validate_Execute)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _stack, _program, &_program[6], _mutex, &_isa); });

	_process->Fetch();

	ASSERT_EQ(_process->opcode, 0x01);

	_process->Decode();

	ASSERT_EQ(typeid(*_process->_instruction), typeid(JMP_L));

	_process->Execute();

	ASSERT_EQ(_process->m_registers.PC, reinterpret_cast<int32_t*>(_program + 0x12));
}