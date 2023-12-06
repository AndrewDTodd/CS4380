#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <cassert>

#include "Allocator.h"

namespace VMFramework
{
	template<typename AllocatedType>
	class PoolAllocator : public Allocator
	{
	private:
		void** m_free_list;

		void* Allocate(const size_t&, const uint8_t&) override { return nullptr; };
	public:
		PoolAllocator(const size_t& size, void* start): Allocator(size, start)
		{
			size_t objectSize;
			size_t objectAlignment;
			if constexpr (sizeof(AllocatedType) < sizeof(void*))
			{
				objectSize = sizeof(void*);
				objectAlignment = alignof(void*);
			}
			else
			{
				objectSize = sizeof(AllocatedType);
				objectAlignment = alignof(AllocatedType);
			}

			//calculate the adjustment needed to keep the objects correctly aligned
			uint8_t adjustment = PointerMath::AlignForwardAdjustment(start, objectAlignment);

			m_free_list = (void**)PointerMath::Add(start, adjustment);

			size_t maxNumOfObjects = (size - adjustment) / objectSize;

			void** p = m_free_list;

			//initialize the free list pointer chain
			for (size_t i = 0; i < maxNumOfObjects - 1; i++)
			{
				*p = PointerMath::Add(p, objectSize);
				p = (void**)*p;
			}

			*p = nullptr;
		}

		~PoolAllocator()
		{
			m_free_list = nullptr;
		}

		void* Allocate()
		{
			if (m_free_list = nullptr)
				return nullptr;

			void* p = m_free_list;

			m_free_list = (void**)(*m_free_list);

			if constexpr (sizeof(AllocatedType) < sizeof(void*))
			{
				m_usedMemory += sizeof(void*);
			}
			else
			{
				m_usedMemory += sizeof(AllocatedType);
			}

			m_numOfAllocations++;

			return p;
		}

		void Deallocate(void* address) override
		{
			*((void**)address) = m_free_list;

			m_free_list = (void**)address;

			if constexpr (sizeof(AllocatedType) < sizeof(void*))
			{
				m_usedMemory -= sizeof(void*);
			}
			else
			{
				m_usedMemory -= sizeof(AllocatedType);
			}

			m_numOfAllocations--;
		}

		PoolAllocator(const PoolAllocator<AllocatedType>&) = delete;
		PoolAllocator<AllocatedType>& operator=(const PoolAllocator<AllocatedType>&) = delete;
		PoolAllocator(PoolAllocator<AllocatedType>&&) = delete;
		PoolAllocator<AllocatedType>& operator=(PoolAllocator<AllocatedType>&&) = delete;
	};
}
#endif // !POOL_ALLOCATOR_H
