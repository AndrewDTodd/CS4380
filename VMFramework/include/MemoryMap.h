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

	/*template<typename T>
	concept DerivedFromPageAllocator = std::derived_from<T, PageAllocator>;*/

	class MemoryMap
	{
	protected:
		const uint8_t* const& m_normalPagePhysicalAddressOrdinal;
		//const size_t m_userSpaceBytes;
		PageAllocator** m_pageAllocators = nullptr;
		const size_t m_numPageAllocators;

		MemoryMap() = default;
		~MemoryMap();

		/// <summary>
		/// Used internally by deriving types to set the m_pageAllocators collection
		/// </summary>
		/// <param name="pageAllocators...">Variadic parameter containing the collection of PageAllocators that the derived Memory Map uses internally/supports</param>
		void SetPageAllocators(const PageAllocator* pageAllocators...);

	public:
		/// <summary>
		/// Called by the MemoryManager to properly set up the Memory Maps resources with the provided systemAllocator resource
		/// </summary>
		/// <param name="systemBytes">The number of bytes available in the systems memory to be managed by the Memory Map sub-system</param>
		/// <param name="systemAllocator">The allocator used at the MemoryManager level to provide access to the systems memory</param>
		virtual void Initialize(const size_t& systemBytes, Allocator* const& systemAllocator) = 0;

		/// <summary>
		/// Used to create a new page of memory in the process's/users address space
		/// </summary>
		/// <param name="pageType">Id representing the type of page that should be created. Supported types determined by the specific MemoryMap implementation</param>
		/// <returns>Pointer to the beggining of the allocated page in memory</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if the page allocator for the specified page type does not have sufficient memory to satisfy the page allocation"/>
		virtual void* AllocateUserPage(const uint8_t& pageType) = 0;

		/// <summary>
		/// Used to create a new page of memory in the system's/kernel's address space
		/// </summary>
		/// <param name="pageType">Id representing the type of page that should be created. Supported types determined by the specific MemoryMap implementation</param>
		/// <returns>Pointer to the beggining of the allocated page in memory</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if the page allocator for the specified page type does not have sufficient memory to satisfy the page allocation"/>
		virtual void* AllocateKernelPage(const uint8_t& pageType) = 0;
		
		/// <summary>
		/// Used to create as many pages as are necessary in the process's/users address space to satisfy the request for memory
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested</param>
		/// <returns>Pointer to the beggining of the set of pages allocated</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if memory map is unable to allocate the required pages for the requested amount of memory"/>
		virtual inline void* AllocateUserPagesFor(const size_t& bytesNeeded) = 0;

		/// <summary>
		/// Used to create as many pages as are necessary in the system's/kernel's address space to satisfy the request for memory
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested</param>
		/// <returns>Pointer to the beggining of the set of pages allocated</returns>
		/// <exception cref="VMFramework::out_of_memory Thrown if memory map is unable to allocate the required pages for the requested amount of memory"/>
		virtual inline void* AllocateKernelPagesFor(const size_t& bytesNeeded) = 0;

		/// <summary>
		/// Used to translate a virtual address into the mapped physical system address in system memory
		/// </summary>
		/// <typeparam name="SystemPtr">The type used by the underlying machine for its virtual addresses/pointers</typeparam>
		/// <param name="virtualAddress">The virtual address to be translated to its associated physical address</param>
		/// <returns>A system address/pointer that is mapped to the provided virtual address</returns>
		template<std::unsigned_integral SystemPtr>
		inline void* Virtual_To_Physical(const SystemPtr& virtualAddress) {};

		/// <summary>
		/// Used to translate a physical system address into the mapped virtual address in the proecess's virtual address space
		/// </summary>
		/// <typeparam name="SystemPtr">The type used by the underlying machine for its virtual addresses/pointers</typeparam>
		/// <param name="physicalAddress">The the system address to be translated to a virtual address</param>
		/// <returns>A virtual address mapped to the provided physical address</returns>
		template<std::unsigned_integral SystemPtr>
		inline SystemPtr Physical_To_Virtual(const void* const& physicalAddress) {};
	};
}
#endif // !MEMORY_MAP_H
