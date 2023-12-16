#ifndef HEAP_CONTAINER_H
#define HEAP_CONTAINER_H

#include <concepts>

#include "IHeapContainer.h"
#include "Allocator.h"

namespace VMFramework
{
	template<typename T>
	concept AllocatorType = std::derived_from<T, VMFramework::Allocator>;

	template<std::integral RegisterType, AllocatorType HeapAllocator>
	class HeapContainer : public IHeapContainer<RegisterType>
	{
	protected:
		HeapAllocator* m_heapAllocator = nullptr;

	public:
		inline void Initialize(const size_t& bytesForHeapAllocator, MemoryMap<RegisterType>* const& memoryMap) override
		{
			size_t heapAllocatedBytes;

			void* heapMemory = memoryMap->AllocateUserPagesFor(bytesForHeapAllocator, true, &heapAllocatedBytes);

			m_heapAllocator = new (heapMemory) HeapAllocator(bytesForHeapAllocator - sizeof(HeapAllocator), PointerMath::Add(heapMemory, sizeof(HeapAllocator)), memoryMap);
		}

		inline void ShutDown() override
		{
			this->m_heapAllocator->ClearAllocator();
			m_heapAllocator->~HeapAllocator();
			this->m_heapAllocator = nullptr;
		}

		inline void* HeapAllocate(const size_t& bytesToAllocate, const uint8_t& alignment) override
		{
			return this->m_heapAllocator->Allocate(bytesToAllocate, alignment);
		}

		inline void HeapFree(void* ptrToFree) override
		{
			this->m_heapAllocator->Deallocate(ptrToFree);
		}

		inline size_t GetHeapUsedMem() override
		{
			return this->m_heapAllocator->GetUsedMemory();
		}

		inline size_t GetHeapNumAlloc() override
		{
			return this->m_heapAllocator->GetNumOfAllocations();
		}
	};
}
#endif // !HEAP_CONTAINER_H
