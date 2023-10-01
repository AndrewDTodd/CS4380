#include <gtest/gtest.h>

#include "../include/StackAllocator.h"

using namespace VMFramework;

//These tests are only valid for Debug build. Code is stripped in Release
#ifdef _DEBUG

class DestroyWithoutDeallocate : public ::testing::Test
{
protected:
	void* _memory;
	StackAllocator* _allocator;

	uint32_t* _test;

	void SetUp() override
	{
		_memory = malloc(20);
		_allocator = new StackAllocator(20, _memory);

		_test = AllocateNew<uint32_t>(sizeof(uint32_t), _allocator);
	}

	void TearDown() override
	{
		delete _allocator;
		free(_memory);
	}
};

class DestroyWithDeallocate : public ::testing::Test
{
protected:
	void* _memory;
	StackAllocator* _allocator;

	uint32_t* _test;

	void SetUp() override
	{
		_memory = malloc(20);
		_allocator = new StackAllocator(20, _memory);

		_test = AllocateNew<uint32_t>(sizeof(uint32_t), _allocator);
		DeallocateDelete<uint32_t>(*_allocator, *_test);
	}

	void TearDown() override
	{
		delete _allocator;
		free(_memory);
	}
};

TEST_F(DestroyWithoutDeallocate, Validate_MemoryLeakDetected)
{
	ASSERT_THROW(delete _allocator, std::runtime_error);
}

TEST_F(DestroyWithDeallocate, Validate_NoMemoryLeakDetected)
{
	ASSERT_NO_THROW(delete _allocator);
}

#endif // _DEBUG

#ifdef _DEBUG
constexpr size_t memNeeded = sizeof(uint32_t) + sizeof(uint8_t) + sizeof(void*);
#else
constexpr size_t memNeeded = sizeof(uint32_t) + sizeof(uint8_t);
#endif // _DEBUG 

class AllocatorForStackOverflow : public ::testing::Test
{
protected:
	void* _memory;
	StackAllocator* _allocator;

	uint32_t* _test;

	void SetUp() override
	{
		_memory = malloc(memNeeded);
		_allocator = new StackAllocator(memNeeded, _memory);

		_test = AllocateNew<uint32_t>(sizeof(uint32_t), _allocator);
	}

	void TearDown() override
	{
		delete _allocator;
		free(_memory);
	}
};

TEST_F(AllocatorForStackOverflow, Validate_StackOverflowDetected)
{
	ASSERT_THROW(AllocateNew<uint32_t>(sizeof(uint32_t), _allocator), stack_overflow);
}