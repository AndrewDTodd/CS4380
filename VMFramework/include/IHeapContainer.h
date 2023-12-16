#ifndef IHEAP_CONTAINER_H
#define IHEAP_CONTAINER_H

#include <cstdint>
#include <cstddef>
#include <concepts>

#include "MemoryMap.h"

namespace VMFramework
{
	template<std::integral RegisterType>
	class IHeapContainer
	{
	public:
		virtual inline void Initialize(const size_t& bytesForHeapAllocator, MemoryMap<RegisterType>* const& memoryMap) = 0;

		virtual inline void ShutDown() = 0;

		virtual inline void* HeapAllocate(const size_t& bytesToAllocate, const uint8_t& alignment) = 0;

		virtual inline void HeapFree(void* ptrToFree) = 0;

		virtual inline size_t GetHeapUsedMem() = 0;

		virtual inline size_t GetHeapNumAlloc() = 0;
	};
}
#endif // !IHEAP_CONTAINER_H
