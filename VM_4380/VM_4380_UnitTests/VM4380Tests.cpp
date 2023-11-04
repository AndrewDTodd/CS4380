#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>

#include "../include/VM4380.h"
#include <Machine.h>

using namespace VMFramework;

class VM4380Testing : public ::testing::Test
{
protected:
	VM4380* _instance;

	uint8_t _program[78] =
	{
		0x06, 0x00, 0x00, 0x00, 0x57, 0x65, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00,
		0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x03, 0x00,
		0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	void SetUp() override
	{
		_instance = VM4380::GetInstance();
	}

	void TearDown() override
	{
	}
};

TEST_F(VM4380Testing, Validate_GetInstance)
{
	ASSERT_EQ(_instance, VM4380::GetInstance());
}

TEST_F(VM4380Testing, Validate_StartUp)
{
	ASSERT_EQ(_instance->m_memoryManager, nullptr);

	ASSERT_NO_THROW({ _instance->StartUp(); });

	ASSERT_NE(_instance->m_memoryManager, nullptr);

#ifdef _DEBUG
	ASSERT_THROW({ _instance->StartUp(); }, std::runtime_error);
#endif // _DEBUG

	ASSERT_NO_THROW({ _instance->ShutDown(); });
}

TEST_F(VM4380Testing, Validate_ShutDown)
{
#ifdef _DEBUG
	ASSERT_THROW({ _instance->ShutDown(); }, std::runtime_error);
#endif // _DEBUG

	ASSERT_NO_THROW({ _instance->StartUp(); });

	ASSERT_NE(_instance->m_memoryManager, nullptr);

	ASSERT_NO_THROW({ _instance->ShutDown(); });
}

TEST_F(VM4380Testing, Validate_LoadProgram)
{
	ASSERT_NO_THROW({ _instance->StartUp(); });

	ASSERT_NE(_instance->m_memoryManager, nullptr);

	ASSERT_NO_THROW({ _instance->LoadProgram(BIN_PATH); });

	ASSERT_NE(_instance->m_programSegment, nullptr);
	ASSERT_EQ(_instance->m_programSize, 78);
	
	for (uint8_t byteNum = 0; byteNum < _instance->m_programSize; byteNum++)
	{
		ASSERT_EQ(_instance->m_programSegment[byteNum], _program[byteNum]);
	}

	ASSERT_NO_THROW({ _instance->ShutDown(); });
}

TEST_F(VM4380Testing, Validate_SpawnProcess)
{
	ASSERT_NO_THROW({ _instance->StartUp(); });

	ASSERT_NE(_instance->m_memoryManager, nullptr);

	_instance->m_programSegment = _program;
	_instance->m_codeSegment = _program + 0x06;
	_instance->m_programSize = 78;

	std::streambuf* originalBuffer = std::cout.rdbuf();

	std::ostringstream capturedOutput;

	std::cout.rdbuf(capturedOutput.rdbuf());

	ASSERT_NO_THROW({ _instance->SpawnProcess(0x06); });

	ASSERT_EQ(_instance->m_processes.size(), 1);
	ASSERT_EQ(_instance->m_processThreads.size(), 1);

	//reset programSegment and codeSegment
	_instance->m_programSegment = nullptr;
	_instance->m_codeSegment = nullptr;

	_instance->WaitForProcess();

	std::cout.rdbuf(originalBuffer);

	ASSERT_NO_THROW({ _instance->ShutDown(); });
}