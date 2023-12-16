#include <gtest/gtest.h>

#include <stdexcept>

#include "../include/MemoryManager.h"
#include "../include/DWORDMemoryMap.h"
#include "../include/ExpandingHeapAllocator.h"
#include "../include/HeapContainer.h"

//These tests will only succeed in Debug mode build as the methods tested only preform test case in Debug mode
#ifdef _DEBUG
class MemoryManagerTesting : public ::testing::Test
{
protected:
	VMFramework::MemoryManager<int32_t>* _manager = nullptr;
	VMFramework::DWORDMemoryMap<int32_t> _memoryMap;
	VMFramework::HeapContainer<int32_t, VMFramework::ExpandingHeapAllocator<int32_t>> heapContainer;

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
	ASSERT_NO_THROW(_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap, VMFramework::MebiByte * 100, heapContainer));

	//Second call should throw runtime_error
	ASSERT_THROW(_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap, VMFramework::MebiByte * 100, heapContainer), std::runtime_error);
}

TEST_F(MemoryManagerTesting, Validate_ShutDownNoStartUpExeption)
{
	ASSERT_THROW(_manager->ShutDown(), std::runtime_error);
	_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap, VMFramework::MebiByte * 100, heapContainer);
}

TEST_F(MemoryManagerTesting, Validate_GetInstanceProducesOneInstance)
{
	_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap, VMFramework::MebiByte * 100, heapContainer);

	VMFramework::MemoryManager<int32_t>* _instance1 = VMFramework::MemoryManager<int32_t>::GetInstance();

	ASSERT_EQ(_manager, _instance1);
}

TEST_F(MemoryManagerTesting, Validate_HeapAllocate)
{
	_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap, VMFramework::MebiByte * 100, heapContainer);

	size_t beforeHeapSize = _manager->GetHeapUsedMem();
	size_t beforeHeapAllocNum = _manager->GetHeapNumAlloc();

	ASSERT_NO_THROW(void* allocatedBlock = _manager->HeapAllocate(255, 1));

	size_t afterHeapSize = _manager->GetHeapUsedMem();
	size_t afterHeapAllocNum = _manager->GetHeapNumAlloc();

	EXPECT_TRUE(afterHeapSize >= (beforeHeapAllocNum + 255));

	EXPECT_EQ((beforeHeapAllocNum++), afterHeapAllocNum);
}

TEST_F(MemoryManagerTesting, Validate_HeapFree)
{
	_manager->StartUp(VMFramework::MebiByte * 400, _memoryMap, VMFramework::MebiByte * 100, heapContainer);

	size_t beforeHeapSize = _manager->GetHeapUsedMem();
	size_t beforeHeapAllocNum = _manager->GetHeapNumAlloc();

	void* allocatedBlock;
	ASSERT_NO_THROW(allocatedBlock = _manager->HeapAllocate(255, 1));

	size_t afterHeapSize = _manager->GetHeapUsedMem();
	size_t afterHeapAllocNum = _manager->GetHeapNumAlloc();

	EXPECT_TRUE(afterHeapSize >= (beforeHeapAllocNum + 255));

	EXPECT_EQ((beforeHeapAllocNum + 1), afterHeapAllocNum);

	ASSERT_NO_THROW(_manager->HeapFree(allocatedBlock));

	EXPECT_EQ(beforeHeapSize, _manager->GetHeapUsedMem());

	EXPECT_EQ(beforeHeapAllocNum, _manager->GetHeapNumAlloc());
}
#endif // _DEBUG