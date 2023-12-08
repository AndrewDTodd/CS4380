#ifndef DWORD_MEMORY_MAP_H
#define DWORD_MEMORY_MAP_H

#include "MemoryMap.h"

#include <filesystem>

namespace VMFramework
{
	class DWORDMemoryMap : MemoryMap
	{
	private:
		struct PageTableEntry
		{
			//frame present in memory, 1, or frame space free, 0
			uint32_t present : 1 = 0;

			//read only frame, 0, or read-write frame, 1
			uint32_t rw : 1 = 0;

			//is this frame in user-space, 1, or in kernel-space 0
			uint32_t user : 1 = 0;

			//page-level write-through enabled, 1, or disabled 0
			//**(enable write-through caching policy, making changes at the CPU cache level be written to RAM immediately.
			//This wont be used in the virtual machine (probably, might be useful for multi-threading))**
			uint32_t pwt : 1 = 0; 

			//page-level caching disabled, 1, or enabled 0 (enabled, 0, is default)
			//**(if the page-level cache disable bit is set then the page wont ever be cached in the CPU cache. Also probably not relevant for the virtual machine)**
			uint32_t pcd : 1 = 0;

			//has the page been accessed since last refresh, 1 if so, 0 if not
			//**(this marks usage of a frame, used by replacement algorithms. last refresh can be in the context of CPU cache or the page being serialized to swap-space)**
			uint32_t accessed : 1 = 0;

			//has the frame been written to since last refresh, 1 if so, 0 if not
			//**(marks if the frame needs to be serialized to either RAM if the page is in cache, or to swap-space if it is in RAM)**
			uint32_t dirty : 1 = 0;

			//used to signify if the page has a 4MiB size, 1, or a 4KiB size, 0
			//**(this is done by having only one entry in the pageTable pointed to by an index in the _pageGlobalDirectory. 
			//   With just one entry we dont need to index into a page table and we can use those 10 bits as part of the offset)**
			uint32_t pse : 1 = 0;

			//is the frame in the global access space (not just local to one process), 1, or is it local to one process, 0
			//**(this can be used to prevent a global frame from being flushed from the translation-lookaside-buffer when a context switch (change of running process) occurs)**
			uint32_t global : 1 = 0;

			uint32_t unused1 : 1 = 0; //can be used by process if desired
			uint32_t unused2 : 1 = 0; //can be used by process if desired
			uint32_t unised3 : 1 = 0; //can be used by process if desired

			//the frame number in memory that we need.
			//Multiply frame_size by frame_number and add to m_physicalAddressOrdinal to get the address of the first byte of the frame
			uint32_t frame_number : 20 = 0;
		};

		//uint32_t* m_pageGlobalDirectory[512];
		uint32_t** m_pageGlobalDirectory;
		const uint16_t m_pageGlobalDirectoryCount;
		uint16_t m_currentPageTable = 0;
		uint16_t m_pageTableNextIndex = 0;
		uint16_t m_normalPageCount = 0;
 
		const uint8_t* const& m_extendedPagesPhysicalAddressOrdinal;
		//uint32_t* m_extendedPageGlobalDirectory[512];
		uint32_t* m_extendedPageGlobalDirectory;
		const uint16_t m_extendedPageGlobalDirectoryCount;
		uint16_t m_nextExtendedPage = 0;
		uint16_t m_extendedPageCount = 0;

	public:
		DWORDMemoryMap() = default;
		~DWORDMemoryMap() = default;

		void Initialize(const size_t& systemBytes, Allocator* const& systemAllocator) override;

		void* AllocatePage(const uint8_t& pageType) override;

		inline void* Virtual_To_Physical(const uint32_t& virtualAddress)
		{

		}

		inline uint32_t Physical_To_Virtual(const void* const& physicalAddress)
		{

		}
	};
}
#endif // !DWORD_MEMORY_MAP_H
