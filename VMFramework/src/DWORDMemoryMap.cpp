#include "../include/DWORDMemoryMap.h"

#include <cassert>

#include "MemoryManager.h"

namespace VMFramework
{
	constexpr size_t allocatorsSize = sizeof(PageAllocator) * 2;
	constexpr size_t pageTableEntriesCount = 1024;

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

		const_cast<uint16_t&>(m_pageGlobalDirectoryCount) = normalPageAllocatorCapacity / pageTableEntriesCount;

		const_cast<uint16_t&> (m_extendedPageGlobalDirectoryCount) = extendedPageAllocatorCapacity / sizeof(FourMiBPage);

#ifdef _DEBUG
		assert(m_pageGlobalDirectoryCount <= 512);
		assert(m_extendedPageGlobalDirectoryCount <= 512);
#endif // _DEBUG
		
		m_pageGlobalDirectory = static_cast<PageTableEntry**>(FourKiBPageAllocator->Allocate<FourKiBPage>());
		const_cast<uint8_t*&>(m_normalPagePhysicalAddressOrdinal) = reinterpret_cast<uint8_t*>(m_pageGlobalDirectory);

		m_extendedPageGlobalDirectory = static_cast<PageTableEntry*>(FourKiBPageAllocator->Allocate<FourKiBPage>());

		m_pageGlobalDirectory[0] = static_cast<PageTableEntry*>(FourKiBPageAllocator->Allocate<FourKiBPage>());

		m_normalPageCount += 3;
	}

	void* DWORDMemoryMap::AllocateUserPage(const uint8_t& pageType)
	{
#ifdef _DEBUG
		assert(pageType < m_numPageAllocators - 1);
#endif // _DEBUG
		
		void* userPageAddress;
		if (pageType == 0)
		{
			userPageAddress = m_pageAllocators[0]->Allocate<FourKiBPage>();
			if (userPageAddress == nullptr)
				throw out_of_memory();

			m_normalPageCount++;

			PageTableEntry entry;
			entry.user = 1;
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
			userPageAddress = m_pageAllocators[1]->Allocate<FourMiBPage>();
			if (userPageAddress == nullptr)
				throw out_of_memory();

			m_extendedPageCount++;

			PageTableEntry entry;
			entry.user = 1;
			entry.present = 1;
			entry.pse = 1;
			entry.frame_number = m_nextExtendedPage;

			m_extendedPageGlobalDirectory[m_nextExtendedPage] = entry;

			m_nextExtendedPage++;
		}

		return userPageAddress;
	}

	void* DWORDMemoryMap::AllocateKernelPage(const uint8_t& pageType)
	{
#ifdef _DEBUG
		assert(pageType < m_numPageAllocators - 1);
#endif // _DEBUG

		void* kernelPageAddress;
		if (pageType == 0)
		{
			kernelPageAddress = m_pageAllocators[0]->Allocate<FourKiBPage>();
			if (kernelPageAddress == nullptr)
				throw out_of_memory();

			m_normalPageCount++;

			PageTableEntry entry;
			entry.user = 0;
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
			kernelPageAddress = m_pageAllocators[1]->Allocate<FourMiBPage>();
			if (kernelPageAddress == nullptr)
				throw out_of_memory();

			m_extendedPageCount++;

			PageTableEntry entry;
			entry.user = 0;
			entry.present = 1;
			entry.pse = 1;
			entry.frame_number = m_nextExtendedPage;

			m_extendedPageGlobalDirectory[m_nextExtendedPage] = entry;

			m_nextExtendedPage++;
		}

		return kernelPageAddress;
	}
}