#ifndef EXPANDING_HEAP_ALLOCATOR_H
#define EXPANDING_HEAP_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <concepts>

#include "Allocator.h"
#include "MemoryManager.h"

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
			uint8_t m_blockFreed : 1 = 0;
			uint8_t m_flag2 : 1 = 0;
			uint8_t _unusedFlagSpace : 7 = 0;
		};

		struct FreeBlock
		{
			size_t m_size;
			FreeBlock* m_next;
		};

		FreeBlock* m_free_blocks;
		FreeBlock* m_last_free_block;

		MemoryMap<RegisterType>* m_memoryMap;

		size_t m_remainingMemory;
		const size_t m_heapBlockSize;

		void ExpandHeap(const size_t& bytesNeeded)
		{
			size_t bytesAllocated;

			void* newPage = m_memoryMap->AllocateUserPagesFor((bytesNeeded > m_heapBlockSize ? bytesNeeded : m_heapBlockSize), true, &bytesAllocated);

			FreeBlock* next_block = (FreeBlock*)newPage;
			next_block->m_size = bytesAllocated;
			next_block->m_next = nullptr;

			m_last_free_block->m_next = next_block;
		}

	public:
		ExpandingHeapAllocator(const size_t& size, void* start, MemoryMap<RegisterType>* const& memoryMap) : 
			Allocator(size, start), m_free_blocks((FreeBlock*)start), m_last_free_block((FreeBlock*)start), m_memoryMap(memoryMap), m_remainingMemory(size), m_heapBlockSize(size + sizeof(ExpandingHeapAllocator))
		{
			assert(size > sizeof(FreeBlock));

			m_free_blocks->m_size = size;
			m_free_blocks->m_next = nullptr;
		}

		~ExpandingHeapAllocator()
		{
			m_free_blocks = nullptr;
			m_last_free_block = nullptr;
			m_memoryMap = nullptr;
			m_remainingMemory = 0;
		}

		inline void* Allocate(const size_t& size, const uint8_t& alignment) override
		{
			assert(size != 0);
			assert(alignment != 0);

			if (m_remainingMemory < size)
				ExpandHeap(size);

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

				//If allocations in the remaining memory of the current free_block will be impossible
				if (free_block->m_size - total_size <= sizeof(AllocationHeader))
				{
					//Increase allocation size instead of creating a new FreeBlock
					total_size = free_block->m_size;

					if (prev_free_block != nullptr)
						prev_free_block->m_next = free_block->m_next;
					else
						m_free_blocks = free_block->m_next;

					if (free_block->m_next == nullptr)
						m_last_free_block = free_block;
				}
				else
				{
					//Else create a new FreeBlock containing remaining memory
					FreeBlock* next_block = (FreeBlock*)(PointerMath::Add(free_block, total_size));
					next_block->m_size = free_block->m_size - total_size;
					next_block->m_next = free_block->m_next;

					if (prev_free_block != nullptr)
						prev_free_block->m_next = next_block;
					else
						m_free_blocks = next_block;

					if (next_block->m_next == nullptr)
						m_last_free_block = next_block;
				}

				uintptr_t aligned_address = (uintptr_t)free_block + adjustment;

				AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader));
				header->m_size = total_size;
				header->m_adjustment = adjustment;
				header->m_blockFreed = 0;

				m_usedMemory += total_size;
				m_remainingMemory -= total_size;
				m_numOfAllocations++;

				assert(PointerMath::AlignForwardAdjustment((void*)aligned_address, alignment) == 0);

				return (void*)aligned_address;
			}

			ExpandHeap(size);
			return Allocate(size, alignment);
		}

		inline void Deallocate(void* p) override
		{
			assert(p != nullptr);

			if (p < m_start || p > static_cast<uint8_t*>(m_start) + m_size)
				throw segmentation_fault("Called free on pointer to memory that wasn't heap allocated");

			AllocationHeader* header = (AllocationHeader*)PointerMath::Subtract(p, sizeof(AllocationHeader));

			if (header->m_blockFreed == 1)
				throw double_free();

			uintptr_t block_start = reinterpret_cast<uintptr_t>(p) - header->m_adjustment;
			size_t block_size = header->m_size;
			uintptr_t block_end = block_start + block_size;

			FreeBlock* prev_free_block = nullptr;
			FreeBlock* free_block = m_free_blocks;

			while (free_block != nullptr)
			{
				if ((uintptr_t)free_block >= block_end)
					break;

				prev_free_block = free_block;
				free_block = free_block->m_next;
			}

			if (prev_free_block == nullptr)
			{
				prev_free_block = (FreeBlock*)block_start;
				prev_free_block->m_size = block_size;
				prev_free_block->m_next = m_free_blocks;

				m_free_blocks = prev_free_block;
			}
			else if ((uintptr_t)prev_free_block + prev_free_block->m_size == block_start)
			{
				prev_free_block->m_size += block_size;
			}
			else
			{
				FreeBlock* temp = (FreeBlock*)block_start;
				temp->m_size = block_size;
				temp->m_next = prev_free_block->m_next;
				prev_free_block->m_next = temp;

				prev_free_block = temp;
			}

			if (free_block != nullptr && (uintptr_t)free_block == block_end)
			{
				prev_free_block->m_size += free_block->m_size;
				prev_free_block->m_next = free_block->m_next;
			}

			m_numOfAllocations--;
			m_usedMemory -= block_size;
			m_remainingMemory += block_size;

			header->m_blockFreed = 1;
		}

		ExpandingHeapAllocator(const ExpandingHeapAllocator&) = delete;
		ExpandingHeapAllocator& operator=(const ExpandingHeapAllocator&) = delete;
		ExpandingHeapAllocator(ExpandingHeapAllocator&&) = delete;
		ExpandingHeapAllocator& operator=(ExpandingHeapAllocator&&) = delete;
	};
}
#endif // !EXPANDING_HEAP_ALLOCATOR_H
