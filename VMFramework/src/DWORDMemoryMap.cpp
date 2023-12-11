#include "../include/DWORDMemoryMap.h"

#include <cassert>

#include "MemoryManager.h"

namespace VMFramework
{
	constexpr size_t allocatorsSize = sizeof(PageAllocator) * 2;
	//constexpr size_t pageTableEntriesCount = 1024;
	constexpr size_t normalPageGlobalDirectoryMaxEntries = 4096 / sizeof(void*);
	constexpr size_t extendedPageGlobalDirectoryMaxEntries = 4096 / 4;

	DWORDMemoryMap::DWORDMemoryMap()
	{}

	DWORDMemoryMap::~DWORDMemoryMap()
	{

	}

	void DWORDMemoryMap::Initialize(const size_t& systemBytes, Allocator* const& systemAllocator)
	{
		size_t pageAllocatorsCapacity = systemBytes - allocatorsSize;
		size_t normalPageAllocatorCapacity, extendedPageAllocatorCapacity;
		normalPageAllocatorCapacity = extendedPageAllocatorCapacity = pageAllocatorsCapacity / 2;

		PageAllocator* FourKiBPageAllocator = AllocateNewAllocator<PageAllocator>(normalPageAllocatorCapacity, systemAllocator);
		PageAllocator* FourMiBPageAllocator = AllocateNewAllocator<PageAllocator>(extendedPageAllocatorCapacity, systemAllocator);

#ifdef _DEBUG
		assert(normalPageAllocatorCapacity == FourKiBPageAllocator->GetSize());
		assert(extendedPageAllocatorCapacity == FourKiBPageAllocator->GetSize());
#endif // _DEBUG

		SetPageAllocators(FourKiBPageAllocator, FourMiBPageAllocator);

		const_cast<uint16_t&>(m_pageGlobalDirectoryCount) = normalPageAllocatorCapacity / BYTES_PER_PAGE_TABLE;

		const_cast<uint16_t&> (m_extendedPageGlobalDirectoryCount) = extendedPageAllocatorCapacity / sizeof(FourMiBPage);

#ifdef _DEBUG
		assert(m_pageGlobalDirectoryCount <= 512);
		assert(m_extendedPageGlobalDirectoryCount <= 512);
#endif // _DEBUG
		
		m_pageGlobalDirectory = reinterpret_cast<PageTableEntry**>(FourKiBPageAllocator->Allocate<FourKiBPage>());
		m_normalPagePhysicalAddressOrdinal = reinterpret_cast<const uint8_t*>(m_pageGlobalDirectory);

		for (size_t pageTableEntryPtr = 0; pageTableEntryPtr < normalPageGlobalDirectoryMaxEntries; pageTableEntryPtr++)
		{
			m_pageGlobalDirectory[pageTableEntryPtr] = nullptr;
		}

		m_extendedPageGlobalDirectory = reinterpret_cast<PageTableEntry*>(FourKiBPageAllocator->Allocate<FourKiBPage>());
		m_extendedPagesPhysicalAddressOrdinal = reinterpret_cast<const uint8_t*>(static_cast<uint8_t*>(FourMiBPageAllocator->GetStart()));

		PageTableEntry defaultEntry;
		defaultEntry.frame_number = 0;
		defaultEntry.present = 0;
		defaultEntry.pse = 1;
		defaultEntry.rw = 0;
		defaultEntry.unused1 = 1;
		for (size_t extendedPageTableEtryIndx = 0; extendedPageTableEtryIndx < extendedPageGlobalDirectoryMaxEntries; extendedPageTableEtryIndx++)
		{
			m_extendedPageGlobalDirectory[extendedPageTableEtryIndx] = defaultEntry;
		}

		m_pageGlobalDirectory[0] = reinterpret_cast<PageTableEntry*>(FourKiBPageAllocator->Allocate<FourKiBPage>());

		m_normalPageCount += 3;
	}
}