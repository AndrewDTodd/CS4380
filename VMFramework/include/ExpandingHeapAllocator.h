#ifndef EXPANDING_HEAP_ALLOCATOR_H
#define EXPANDING_HEAP_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <concepts>

#include "Allocator.h"
#include "MemoryMap.h"

namespace VMFramework
{
	template<std::integral RegisterType>
	class ExpandingHeapAllocator : public Allocator
	{
	private:
		struct AllocationHeader
		{
			size_t m_size;
			uint8_t m_adjustment;
		};

		struct FreeBlock
		{
			size_t m_size;
			FreeBlock* m_next;
		};

		FreeBlock* m_free_blocks;

		MemoryMap<RegisterType>* m_memoryMap;

	public:
		ExpandingHeapAllocator::ExpandingHeapAllocator(const size_t& size, void* start, MemoryMap<RegisterType>& memoryMap) : 
			Allocator(size, start), m_free_blocks((FreeBlock*)start), m_memoryMap(&memoryMap)
		{
			static_assert(size > sizeof(FreeBlock));

			m_free_blocks->m_size = size;
			m_free_blocks->m_next = nullptr;
		}

		ExpandingHeapAllocator::~ExpandingHeapAllocator()
		{
			m_free_blocks = nullptr;
		}

		void* Allocate(const size_t& size, const uint8_t& alignment) override
		{
			static_assert(size != 0, "Allocation of zero byte block is not permitted");
			static_assert(alignment != 0, "Allignment of allocated block can't be 0 bytes");

			FreeBlock* prev_free_block = nullptr;
			FreeBlock* free_block = m_free_blocks;

			while (free_block != nullptr)
			{
				//Calculate adjustment needed to keep block correctly aligned
				uint8_t adjustment = PointerMath::AlignForwardAdjustmentWithHeader(free_block, alignment, sizeof(AllocationHeader));

				size_t total_size = size + adjustment;

				//If allocation doesn't fit in this FreeBlock, try the next
				if (free_block->m_size < total_size)
				{
					prev_free_block = free_block;
					free_block = free_block->m_next;
					continue;
				}

				static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)");

				//If allocations in the remaining memory will be impossible
				if (free_block->m_size - total_size <= sizeof(AllocationHeader))
				{
					//Increase allocation size instead of creating a new FreeBlock
					total_size = free_block->m_size;

					if (prev_free_block != nullptr)
						prev_free_block->m_next = free_block->m_next;
					else
						m_free_blocks = free_block->m_next;
				}
				else
				{
					//Else create a new FreeBlock containing remaining memory
					FreeBlock* next_block = (FreeBlock*)(pointer_math::add(free_block, total_size));
					next_block->m_size = free_block->m_size - total_size;
					next_block->m_next = free_block->m_next;

					if (prev_free_block != nullptr)
						prev_free_block->m_next = next_block;
					else
						m_free_blocks = next_block;
				}

				uintptr_t aligned_address = (uintptr_t)free_block + adjustment;

				AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader));
				header->m_size = total_size;
				header->m_adjustment = adjustment;

				m_usedMemory += total_size;
				m_numOfAllocations++;

				assert(pointer_math::alignForwardAdjustment((void*)aligned_address, alignment) == 0);

				return (void*)aligned_address;
			}
		}

		void Deallocate(void* p) override;

		ExpandingHeapAllocator(const ExpandingHeapAllocator&) = delete;
		ExpandingHeapAllocator& operator=(const ExpandingHeapAllocator&) = delete;
		ExpandingHeapAllocator(ExpandingHeapAllocator&&) = delete;
		ExpandingHeapAllocator& operator=(ExpandingHeapAllocator&&) = delete;
	};
}
#endif // !EXPANDING_HEAP_ALLOCATOR_H
