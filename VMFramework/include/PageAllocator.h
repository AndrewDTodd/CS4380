#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>

#include "Allocator.h"

namespace VMFramework
{
	class PageAllocator : public Allocator
	{
	private:
		void* m_currentPosition;

		void* Allocate(const size_t&, const uint8_t&) override { return nullptr; };
		void Deallocate(void*) override {};
	public:
		/*enum PageSize
		{
			normal,
			extended
		};*/

		PageAllocator(const size_t& size, void* start);
		~PageAllocator();

		template<class PageType>
		void* Allocate()
		{
			uint8_t adjustment = PointerMath::AlignForwardAdjustment(m_currentPosition, alignof(void*));

			if (m_usedMemory + adjustment + sizeof(PageType) > m_size)
				return nullptr;

			void* aligned_address = PointerMath::Add(m_currentPosition, adjustment);

			m_currentPosition = PointerMath::Add(aligned_address, sizeof(PageType));

			m_usedMemory += sizeof(PageType) + adjustment;

			m_numOfAllocations++;

			return aligned_address;
		}

		void Clear();

		PageAllocator(const PageAllocator&) = delete;
		PageAllocator& operator=(const PageAllocator&) = delete;
		PageAllocator(PageAllocator&&) = delete;
		PageAllocator& operator=(PageAllocator&&) = delete;
	};
}
#endif // !PAGE_ALLOCATOR_H
