#include <gtest/gtest.h>

#include <stdexcept>

#include "../include/MemoryManager.h"

//These tests will only succeed in Debug mode build as the methods tested only preform function in Debug mode
#ifdef _DEBUG
class MemoryManagerTesting : public ::testing::Test
{
protected:
	VMFramework::MemoryManager* _manager = nullptr;

	void SetUp() override
	{
		_manager = VMFramework::MemoryManager::GetInstance();
	}

	void TearDown() override
	{
		_manager->ShutDown();
		_manager = nullptr;
	}
};

TEST_F(MemoryManagerTesting, DoubleStartUpExeption)
{
	//First call to StartUp is valid
	ASSERT_NO_THROW(_manager->StartUp());

	//Second call should throw runtime_error
	ASSERT_THROW(_manager->StartUp(), std::runtime_error);
}

TEST_F(MemoryManagerTesting, GetInstanceProducesOneInstance)
{
	VMFramework::MemoryManager* _instance1 = VMFramework::MemoryManager::GetInstance();

	ASSERT_EQ(_manager, _instance1);
}
#endif // _DEBUG