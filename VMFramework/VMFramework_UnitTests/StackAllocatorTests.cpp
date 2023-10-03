#include <gtest/gtest.h>

#include "../include/Allocator.h"
#include "../include/StackAllocator.h"

using namespace VMFramework;

#ifdef _DEBUG
constexpr size_t memNeeded = sizeof(uint32_t) + alignof(int32_t) + sizeof(uint8_t) + alignof(uint32_t) + sizeof(void*) + sizeof(StackAllocator);
#else
constexpr size_t memNeeded = sizeof(uint32_t) + alignof(int32_t) + sizeof(uint8_t) + sizeof(StackAllocator);
#endif // _DEBUG

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
		_memory = malloc(memNeeded);
		_allocator = new (_memory) StackAllocator(memNeeded - sizeof(StackAllocator), PointerMath::Add(_memory, sizeof(StackAllocator)));

		_test = AllocateNew<uint32_t>(sizeof(uint32_t), *_allocator);
	}

	void TearDown() override
	{
		//If free is called here Abort happens claiming free has been called ????
		//free(_memory);
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
		_memory = malloc(memNeeded);
		_allocator = new (_memory) StackAllocator(memNeeded - sizeof(StackAllocator), PointerMath::Add(_memory, sizeof(StackAllocator)));

		_test = AllocateNew<uint32_t>(sizeof(uint32_t), *_allocator);
		DeallocateDelete<uint32_t>(*_allocator, *_test);
	}

	void TearDown() override
	{
		//free(_memory);
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

TEST(AllocatorTests, Validate_NullStartThrowsExeption)
{
	ASSERT_THROW(StackAllocator(0, nullptr), std::invalid_argument);
}
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
		_allocator = new (_memory) StackAllocator(memNeeded - sizeof(StackAllocator), PointerMath::Add(_memory, sizeof(StackAllocator)));

		_test = AllocateNew<uint32_t>(sizeof(uint32_t), *_allocator);
	}

	void TearDown() override
	{
		DeallocateDelete<uint32_t>(*_allocator, *_test);
		delete _allocator;
		//free(_memory);
	}
};

TEST_F(AllocatorForStackOverflow, Validate_StackOverflowDetected)
{
	ASSERT_THROW(AllocateNew<uint32_t>(sizeof(uint32_t), *_allocator), stack_overflow);
}