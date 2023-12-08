#include "../include/DWORDMemoryMap.h"

#include <cassert>

#include "MemoryManager.h"

namespace VMFramework
{
	constexpr size_t allocatorsSize = sizeof(PageAllocator) * 2;
	constexpr size_t pageTableEntriesCount = 1024;

	struct FourKiBPage
	{
		uint8_t[4096];
	};

	struct FourMiBPage
	{
		uint8_t[MebiByte * 4];
	};

	void DWORDMemoryMap::Initialize(const size_t& systemBytes, Allocator* const& systemAllocator)
	{
		size_t pageAllocatorsCapacity = systemBytes - allocatorsSize;
		size_t normalPageAllocatorCapacity, extendedPageAllocatorCapacity = pageAllocatorsCapacity / 2;

		PageAllocator* FourKiBPageAllocator = AllocateNewAllocator<PageAllocator>(normalPageAllocatorCapacity, systemAllocator);
		PageAllocator* FourMiBPageAllocator = AllocateNewAllocator<PageAllocator>(extendedPageAllocatorCapacity, systemAllocator);

#ifdef _DEBUG
		assert(normalPageAllocatorCapacity == FourKiBPageAllocator->GetSize());
		assert(extendedPageAllocatorCapacity == FourKiBPageAllocator->GetSize());
#endif // _DEBUG

		SetPageAllocators(FourKiBPageAllocator, FourMiBPageAllocator);

		const_cast<uint16_t>&(m_pageGlobalDirectoryCount) = normalPageAllocatorCapacity / pageTableEntriesCount;

		const_cast<uint16_t>& (m_extendedPageGlobalDirectoryCount) = extendedPageAllocatorCapacity / sizeof(FourMiBPage);

#ifdef _DEBUG
		assert(m_pageGlobalDirectoryCount <= 512);
		assert(m_extendedPageGlobalDirectoryCount <= 512);
#endif // _DEBUG
		
		m_normalPagePhysicalAddressOrdinal = static_cast<uint8_t*>(FourKiBPageAllocator->Allocate<FourKiBPage>());
		m_pageGlobalDirectory = m_normalPagePhysicalAddressOrdinal;
		m_extendedPageGlobalDirectory = static_cast<uint32_t*>(FourKiBPageAllocator->Allocate<FourKiBPage>());

		m_pageGlobalDirectory[0] = static_cast<uint32_t*>(FourKiBPageAllocator->Allocate<FourKiBPage>());

		m_normalPageCount += 3;
	}

	void* DWORDMemoryMap::AllocatePage(const uint8_t& pageType)
	{
#ifdef _DEBUG
		assert(pageType < m_numPageAllocators - 1);
#endif // _DEBUG

		if (pageType == 0)
		{
			if (m_pageAllocators[0]->Allocate<FourKiBPage>() == nullptr)
				throw out_of_memory;

			m_normalPageCount++;

			PageTableEntry entry;
			entry.present = 1;
			entry.frame_number = m_pageTableNextIndex;

			m_pageGlobalDirectory[m_currentPageTable][m_pageTableNextIndex] = entry;
			m_pageTableNextIndex++;

			if (m_pageTableNextIndex == 1024)
			{
				m_currentPageTable++;
#ifdef _DEBUG
				assert(m_currentPageTable < m_pageGlobalDirectoryCount);
#endif // _DEBUG

				m_pageTableNextIndex = 0;
			}
		}
		else
		{
			if (m_pageAllocators[1]->Allocate<FourMiBPage>() == nullptr)
				throw out_of_memory;

			m_extendedPageCount++;
			
			PageTableEntry entry;
			entry.present = 1;
			entry.pse = 1;
			entry.frame_number = m_nextExtendedPage;

			m_extendedPageGlobalDirectory[m_nextExtendedPage][0] = entry;

			m_nextExtendedPage++;
		}
	}
}