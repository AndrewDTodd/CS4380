#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <cstdint>
#include <cstddef>

#include "PageAllocator.h"

namespace VMFramework
{
	class out_of_memory : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Page Allocator is out of memory";
		}
	};

	/*template<std::unsigned_integral SystemPtr>
	class segmentation_fault : public std::exception
	{
	private:
		const SystemPtr _virtualAddress;
	public:
		explicit segmentation_fault(const SystemPtr& virtualAddress) : _virtualAddress(virtualAddress)
		{}

		const char* what() const noexcept override
		{
			std::stringstream stream << "Segmentation Fault. Provided address is not valid: 0x" << std::hex << _virtualAddress;
			return stream.str().c_str();
		}
	};*/

	template<typename T>
	concept PageAllocatorType = std::is_same_v<T, PageAllocator>;

	template<std::integral RegisterType>
	class MemoryMap
	{
	protected:
		const uint8_t* m_normalPagePhysicalAddressOrdinal = nullptr;
		PageAllocator** m_pageAllocators = nullptr;
		const size_t m_numPageAllocators = 0;

		MemoryMap()
		{}

		virtual ~MemoryMap()
		{
			for (size_t pageAllocator = 0; pageAllocator < m_numPageAllocators; pageAllocator++)
			{
				m_pageAllocators[pageAllocator]->Clear();
			}

			delete[] m_pageAllocators;
			m_pageAllocators = nullptr;
			m_normalPagePhysicalAddressOrdinal = nullptr;
			const_cast<size_t&>(m_numPageAllocators) = 0;
		}

		/// <summary>
		/// Used internally by deriving types to set the m_pageAllocators collection
		/// </summary>
		/// <param name="pageAllocators...">Variadic parameter containing the collection of PageAllocators that the derived Memory Map uses internally/supports</param>
		template<PageAllocatorType... Page_Allocators>
		void SetPageAllocators(Page_Allocators*... pageAllocators)
		{
#ifdef _DEBUG
			assert(m_pageAllocators == nullptr);
#endif // _DEBUG

			constexpr size_t numAllocators = sizeof...(pageAllocators);
			const_cast<size_t&>(m_numPageAllocators) = numAllocators;

			m_pageAllocators = new PageAllocator* [numAllocators] {pageAllocators...};
		}

	public:
		enum PageReadWrite
		{
			readonly = false,
			read_write = true
		};

		/// <summary>
		/// Called by the MemoryManager to properly set up the Memory Maps resources with the provided systemAllocator resource
		/// </summary>
		/// <param name="systemBytes">The number of bytes available in the systems memory to be managed by the Memory Map sub-system</param>
		/// <param name="systemAllocator">The allocator used at the MemoryManager level to provide access to the systems memory</param>
		virtual void Initialize(const size_t& systemBytes, Allocator* const& systemAllocator) = 0;

		virtual void ShutDown()
		{
			this->~MemoryMap();
		}

		/// <summary>
		/// Used to create a new page of memory in the process's/users address space
		/// </summary>
		/// <param name="pageType">Id representing the type of page that should be created. Supported types determined by the specific MemoryMap implementation</param>
		/// <returns>Pointer to the beggining of the allocated page in memory</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if the page allocator for the specified page type does not have sufficient memory to satisfy the page allocation"/>
		virtual inline void* AllocateUserPage(const uint8_t& pageType, const bool& pageWritable) = 0;

		/// <summary>
		/// Used to create a new page of memory in the system's/kernel's address space
		/// </summary>
		/// <param name="pageType">Id representing the type of page that should be created. Supported types determined by the specific MemoryMap implementation</param>
		/// <returns>Pointer to the beggining of the allocated page in memory</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if the page allocator for the specified page type does not have sufficient memory to satisfy the page allocation"/>
		virtual inline void* AllocateKernelPage(const uint8_t& pageType, const bool& pageWritable) = 0;
		
		/// <summary>
		/// Used to create as many pages as are necessary in the process's/users address space to satisfy the request for memory
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested</param>
		/// <returns>Pointer to the beggining of the set of pages allocated</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if memory map is unable to allocate the required pages for the requested amount of memory"/>
		virtual inline void* AllocateUserPagesFor(const size_t& bytesNeeded, const bool& pageWritable) = 0;

		/// <summary>
		/// Used to create as many pages as are necessary in the system's/kernel's address space to satisfy the request for memory
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested</param>
		/// <returns>Pointer to the beggining of the set of pages allocated</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if memory map is unable to allocate the required pages for the requested amount of memory"/>
		virtual inline void* AllocateKernelPagesFor(const size_t& bytesNeeded, const bool& pageWritable) = 0;

		/// <summary>
		/// Used to free any number of contiguouse pages that start at the address provided
		/// </summary>
		/// <param name="pagesStart">Pointer to the beginning of the first page in the sequence</param>
		/// <param name="pagesBytes">The length in bytes of the sequence to free</param>
		virtual inline void FreePages(void* pagesStart, const size_t& pagesBytes) = 0;

		/// <summary>
		/// Used to translate a virtual address into the mapped physical system address in system memory
		/// </summary>
		/// <param name="virtualAddress">The virtual address to be translated to its associated physical address</param>
		/// <returns>A system address/pointer that is mapped to the provided virtual address</returns>
		virtual inline void* Virtual_To_Physical(const RegisterType& virtualAddress) = 0;

		/// <summary>
		/// Used to translate a physical system address into the mapped virtual address in the proecess's virtual address space
		/// </summary>
		/// <param name="physicalAddress">The the system address to be translated to a virtual address</param>
		/// <returns>A virtual address mapped to the provided physical address</returns>
		virtual inline RegisterType Physical_To_Virtual(const void* const& physicalAddress) = 0;
	};
}
#endif // !MEMORY_MAP_H
