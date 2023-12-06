#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>

#include "Allocator.h"

namespace VMFramework
{
	class PageAllocator : Allocator
	{
	private:
		void* m_currentPosition;

		void* Allocate(const size_t&, const uint8_t&) override { return nullptr; };
		void Deallocate(void*) override {};
	public:
		enum PageSize
		{
			normal,
			extended
		};

		PageAllocator(const size_t& size, void* start);
		~PageAllocator();

		template<class PageType>
		void* Allocate()
		{
			if (m_usedMemory + sizeof(PageType) > m_size)
				return nullptr;

			uintptr_t pageAddress = (uintptr_t)m_currentPosition;
			m_currentPosition = (void*)(pageAddress + sizeof(PageType));

			m_usedMemory += sizeof(PageType);
			m_numOfAllocations++;

			return (void*)pageAddress;
		}

		void Clear();

		PageAllocator(const PageAllocator&) = delete;
		PageAllocator& operator=(const PageAllocator&) = delete;
		PageAllocator(PageAllocator&&) = delete;
		PageAllocator& operator=(PageAllocator&&) = delete;
	};
}
#endif // !PAGE_ALLOCATOR_H
