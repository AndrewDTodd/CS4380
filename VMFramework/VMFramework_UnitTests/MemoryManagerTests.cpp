#include <gtest/gtest.h>

#include <stdexcept>

#include "../include/MemoryManager.h"
#include "../include/DWORDMemoryMap.h"

//These tests will only succeed in Debug mode build as the methods tested only preform test case in Debug mode
#ifdef _DEBUG
class MemoryManagerTesting : public ::testing::Test
{
protected:
	VMFramework::MemoryManager<int32_t>* _manager = nullptr;
	VMFramework::DWORDMemoryMap<int32_t> _memoryMap;

	void SetUp() override
	{
		_manager = VMFramework::MemoryManager<int32_t>::GetInstance();
	}

	void TearDown() override
	{
		_manager->ShutDown();
		_manager = nullptr;
	}
};

TEST_F(MemoryManagerTesting, Validate_DoubleStartUpExeption)
{
	//First call to StartUp is valid
	ASSERT_NO_THROW(_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap));

	//Second call should throw runtime_error
	ASSERT_THROW(_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap), std::runtime_error);
}

TEST_F(MemoryManagerTesting, Validate_ShutDownNoStartUpExeption)
{
	ASSERT_THROW(_manager->ShutDown(), std::runtime_error);
	_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap);
}

TEST_F(MemoryManagerTesting, Validate_GetInstanceProducesOneInstance)
{
	_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap);

	VMFramework::MemoryManager<int32_t>* _instance1 = VMFramework::MemoryManager<int32_t>::GetInstance();

	ASSERT_EQ(_manager, _instance1);
}
#endif // _DEBUG