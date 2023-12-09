#ifndef DWORD_MEMORY_MAP_H
#define DWORD_MEMORY_MAP_H

#include "MemoryMap.h"

#include <filesystem>

namespace VMFramework
{
	static constexpr uint64_t MebiByte = 1048576;
	static constexpr size_t SIZE_OF_NORMAL_PAGE = 4096;
	static constexpr size_t NUM_OF_ENTRIES_PER_PAGE_TABLE = 1024;
	static constexpr size_t NUM_OF_ENTRIES_IN_GLOBAL_DIR = 512;
	static constexpr size_t BYTES_IN_NORMAL_PAGE_SPACE = NUM_OF_ENTRIES_IN_GLOBAL_DIR * NUM_OF_ENTRIES_PER_PAGE_TABLE * SIZE_OF_NORMAL_PAGE;
	static constexpr size_t BYTES_PER_PAGE_TABLE = NUM_OF_ENTRIES_PER_PAGE_TABLE * SIZE_OF_NORMAL_PAGE;

	class DWORDMemoryMap : MemoryMap
	{
	private:
		struct FourKiBPage
		{
			uint8_t bytes[4096];
		};

		struct FourMiBPage
		{
			uint8_t bytes[MebiByte * 4];
		};

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
			//With just one entry we dont need to index into a page table and we can use those 10 bits as part of the offset)**
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

		struct DWORDVirtualAddress
		{
			uint32_t pageGlobalDirectoryIndex : 10 = 0;
			uint32_t pageTableIndex : 10 = 0;
			uint32_t pageOffset : 12 = 0;
		};

		struct DWORDExtendedPageAddress
		{
			uint32_t pageGlobalDirectoryIndex : 10 = 0;
			uint32_t pageOffset : 22 = 0;
		};

		//uint32_t* m_pageGlobalDirectory[512];
		PageTableEntry** m_pageGlobalDirectory;
		const uint16_t m_pageGlobalDirectoryCount;
		uint16_t m_currentPageTable = 0;
		uint16_t m_pageTableNextIndex = 0;
		uint16_t m_normalPageCount = 0;
 
		const uint8_t* const& m_extendedPagesPhysicalAddressOrdinal;
		//uint32_t* m_extendedPageGlobalDirectory[512];
		PageTableEntry* m_extendedPageGlobalDirectory;
		const uint16_t m_extendedPageGlobalDirectoryCount;
		uint16_t m_nextExtendedPage = 0;
		uint16_t m_extendedPageCount = 0;

	public:
		DWORDMemoryMap() = default;
		~DWORDMemoryMap() = default;

		///<inheritdoc/>
		void Initialize(const size_t& systemBytes, Allocator* const& systemAllocator) override;

		/// <summary>
		/// Used to create a new page of memory in the process's/users address space
		/// </summary>
		/// <param name="pageType">Id representing the type of page that should be created. 0 for normal page(4KiB), 1 for extended page(4MiB)</param>
		/// <returns>Pointer to the beggining of the allocated page in memory</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if the page allocator for the specified page type does not have sufficient memory to satisfy the page allocation"/>
		void* AllocateUserPage(const uint8_t& pageType) override;

		/// <summary>
		/// Used to create a new page of memory in the system's/kernel's address space
		/// </summary>
		/// <param name="pageType">Id representing the type of page that should be created. 0 for normal page(4KiB), 1 for extended page(4MiB)</param>
		/// <returns>Pointer to the beggining of the allocated page in memory</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if the page allocator for the specified page type does not have sufficient memory to satisfy the page allocation"/>
		void* AllocateKernelPage(const uint8_t& pageType) override;

		/// <summary>
		/// Used to create as many pages as are necessary in the process's/users address space to satisfy the request for memory
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested</param>
		/// <returns>Pointer to the beggining of the set of pages allocated</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if memory map is unable to allocate the required pages for the requested amount of memory"/>
		inline void* AllocateUserPagesFor(const size_t& bytesNeeded) override
		{
			size_t numPagesNeeded;
			void* addressFirstPage;

			if (bytesNeeded > sizeof(FourMiBPage) - 4096 && bytesNeeded % sizeof(FourMiBPage) < 4096)
			{
				numPagesNeeded = bytesNeeded / sizeof(FourMiBPage);
				if (bytesNeeded % sizeof(FourMiBPage) != 0)
					numPagesNeeded++;

				addressFirstPage = AllocateUserPage(1);

				for (size_t page = 1; page < numPagesNeeded; page++)
				{
					AllocateUserPage(1);
				}

				return addressFirstPage;
			}
			else
			{
				numPagesNeeded = bytesNeeded / sizeof(FourKiBPage);
				if (bytesNeeded % sizeof(FourKiBPage) != 0)
					numPagesNeeded++;

				addressFirstPage = AllocateUserPage(0);

				for (size_t page = 1; page < numPagesNeeded; page++)
				{
					AllocateUserPage(0);
				}

				return addressFirstPage;
			}
		}

		/// <summary>
		/// Used to create as many pages as are necessary in the system's/kernel's address space to satisfy the request for memory
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested</param>
		/// <returns>Pointer to the beggining of the set of pages allocated</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if memory map is unable to allocate the required pages for the requested amount of memory"/>
		inline void* AllocateKernelPagesFor(const size_t& bytesNeeded) override
		{
			size_t numPagesNeeded;
			void* addressFirstPage;

			if (bytesNeeded > sizeof(FourMiBPage) - 4096 && bytesNeeded % sizeof(FourMiBPage) < 4096)
			{
				numPagesNeeded = bytesNeeded / sizeof(FourMiBPage);
				if (bytesNeeded % sizeof(FourMiBPage) != 0)
					numPagesNeeded++;

				addressFirstPage = AllocateKernelPage(1);

				for (size_t page = 1; page < numPagesNeeded; page++)
				{
					AllocateKernelPage(1);
				}

				return addressFirstPage;
			}
			else
			{
				numPagesNeeded = bytesNeeded / sizeof(FourKiBPage);
				if (bytesNeeded % sizeof(FourKiBPage) != 0)
					numPagesNeeded++;

				addressFirstPage = AllocateKernelPage(0);

				for (size_t page = 1; page < numPagesNeeded; page++)
				{
					AllocateKernelPage(0);
				}

				return addressFirstPage;
			}
		}

		/// <summary>
		/// Used to convert a virtual address into the associated physical address
		/// </summary>
		/// <param name="virtualAddress">The internal virtual address needing translation</param>
		/// <returns>Pointer to the physical address in the system's memory</returns>
		inline void* Virtual_To_Physical(const uint32_t& virtualAddress)
		{
			PageTableEntry pte;
			uint8_t* physicalAddress;

			const DWORDVirtualAddress pageAddress = reinterpret_cast<const DWORDVirtualAddress&>(virtualAddress);

			//This means the virtual address is to an extended page
			if (pageAddress.pageGlobalDirectoryIndex > 511)
			{
				const DWORDExtendedPageAddress extendedPageAddress = reinterpret_cast<const DWORDExtendedPageAddress&>(pageAddress);

				if (extendedPageAddress.pageGlobalDirectoryIndex > m_extendedPageCount)
					throw std::invalid_argument("The global directory index portion of the virtual address is not valid");

				pte = m_extendedPageGlobalDirectory[extendedPageAddress.pageGlobalDirectoryIndex];

				physicalAddress = const_cast<uint8_t*&>(m_extendedPagesPhysicalAddressOrdinal) + (pte.frame_number * sizeof(FourMiBPage)) + extendedPageAddress.pageOffset;
			}
			//This means the virtual address is to a normal page
			else
			{
				if (pageAddress.pageGlobalDirectoryIndex > m_currentPageTable)
					throw std::invalid_argument("The global directory index portion of the virtual address is not valid");
				else if (pageAddress.pageGlobalDirectoryIndex == m_currentPageTable && pageAddress.pageTableIndex >= m_pageTableNextIndex)
					throw std::invalid_argument("The page table index portion of the virtual address is not valid");

				pte = m_pageGlobalDirectory[pageAddress.pageGlobalDirectoryIndex][pageAddress.pageTableIndex];

				physicalAddress = const_cast<uint8_t*&>(m_normalPagePhysicalAddressOrdinal) + (pte.frame_number * sizeof(FourKiBPage)) + pageAddress.pageOffset;
			}

			return physicalAddress;
		}

		/// <summary>
		/// Used to convert a physical address in the systems memory into a virtual address
		/// </summary>
		/// <param name="physicalAddress">The physical system address to translate into a virtual address</param>
		/// <returns>The virtual address mapped to the provided physical address</returns>
		inline uint32_t Physical_To_Virtual(const void* const& physicalAddress)
		{
			if (physicalAddress < m_normalPagePhysicalAddressOrdinal)
				throw std::invalid_argument("The address provided for translation is not within our pagable address space");

			uintptr_t offset;

			//The physical address is in the range of extended page addresses
			if (physicalAddress >= m_extendedPagesPhysicalAddressOrdinal)
			{
				offset = reinterpret_cast<uintptr_t>(physicalAddress) - reinterpret_cast<uintptr_t>(m_extendedPagesPhysicalAddressOrdinal);

				DWORDExtendedPageAddress virtualAddress;
				virtualAddress.pageGlobalDirectoryIndex = offset / sizeof(FourMiBPage) + 512;
				virtualAddress.pageOffset = offset % sizeof(FourMiBPage);

				return *reinterpret_cast<uint32_t*>(&virtualAddress);
			}
			//The physical address is in the range of normal page addresses
			else
			{
				offset = reinterpret_cast<uintptr_t>(physicalAddress) - reinterpret_cast<uintptr_t>(m_normalPagePhysicalAddressOrdinal);

				DWORDVirtualAddress virtualAddress;
				virtualAddress.pageGlobalDirectoryIndex = offset / BYTES_IN_NORMAL_PAGE_SPACE;
				virtualAddress.pageTableIndex = (offset % BYTES_IN_NORMAL_PAGE_SPACE) / BYTES_PER_PAGE_TABLE;
				virtualAddress.pageOffset = (offset % BYTES_PER_PAGE_TABLE) / SIZE_OF_NORMAL_PAGE;

				return *reinterpret_cast<uint32_t*>(&virtualAddress);
			}
		}
	};
}
#endif // !DWORD_MEMORY_MAP_H
