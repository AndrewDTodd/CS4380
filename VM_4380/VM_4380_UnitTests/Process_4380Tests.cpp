#include <gtest/gtest.h>

#include <stdexcept>
#include <shared_mutex>
#include <cstdint>

#include "../include/Instructions/VM_Instructions.h"

#include "../include/Process_4380.h"
#include "../include/ISA_4380.h"
#include "../include/DWORDMemoryMap.h"

using namespace VMFramework;

class Process_4380Testing : public ::testing::Test
{
protected:
	std::shared_mutex _mutex;

	MemoryManager<int32_t>* _memoryManager;
	DWORDMemoryMap<int32_t> _memoryMap;

	void* stackMemory;

	ISA_4380 _isa;

	uint8_t* _program;
	uint8_t programCode[78] =
	{
		0x06, 0x00, 0x00, 0x00, 0x57, 0x65, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00,
		0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00,
		0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	void SetUp() override
	{
		_memoryManager = MemoryManager<int32_t>::GetInstance();
		_memoryManager->StartUp(VMFramework::MebiByte, _memoryMap);

		_program = static_cast<uint8_t*>(_memoryManager->AllocateUserPage(DWORDMemoryMap<int32_t>::PageTypes::normal));

		std::memcpy(_program, programCode, 78);

		stackMemory = _memoryManager->AllocateUserPagesFor(100);
	}

	void TearDown() override
	{
		_memoryManager->ShutDown();
	}
};

//Process_4380(void* initialPC, StackAllocator* processStack, uint8_t* programStart, uint8_t* codeSegmentStart, std::shared_mutex& machineMutex, ISA_4380* isa);
TEST_F(Process_4380Testing, Validate_ConstructorValidInput)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);});
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnNullProgramPointer)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], nullptr, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnNullCodeSegmentPointer)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], _program, nullptr, &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnNullProgramEndPointer)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], _program, &_program[6], nullptr, &_isa, _mutex, _memoryManager, 100, stackMemory);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnInvalidCodeStart)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[6], _program, _program - 1, &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnPCInDataSegment)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(&_program[5], _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);}, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_ConstructorThrowsOnInvalidPC)
{
	Process_4380* _process;

	ASSERT_THROW({ _process = new Process_4380(nullptr, _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory); }, std::runtime_error);
	ASSERT_THROW({ _process = new Process_4380(_program - 1, _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory); }, std::runtime_error);
}

TEST_F(Process_4380Testing, Validate_Fetch)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);});

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

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);});

	_process->Increment();

	ASSERT_EQ(_memoryManager->Virtual_To_Physical(_process->m_registers[16]), _program + 0x12);
}

TEST_F(Process_4380Testing, Validate_Decode)
{
	Process_4380* _process;

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);});

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

	ASSERT_NO_THROW({ _process = new Process_4380(&_program[6], _program, &_program[6], &_program[77], &_isa, _mutex, _memoryManager, 100, stackMemory);});

	_process->Fetch();

	ASSERT_EQ(_process->opcode, 0x01);

	_process->Decode();

	ASSERT_EQ(typeid(*_process->_instruction), typeid(JMP_L));

	_process->Execute();

	ASSERT_EQ(_program + _process->m_registers[16], _program + 0x12);
}