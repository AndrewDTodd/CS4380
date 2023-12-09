#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <cstdint>
#include <thread>
#include <shared_mutex>
#include <concepts>

#include "StackAllocator.h"
#include "MemoryMap.h"

//#define TOTAL_GIBIGYTES_FOR_SYSTEM 1

namespace VMFramework
{
	constexpr size_t GibiByte = 1073741824;
	constexpr size_t MebiByte = 1048576;
	constexpr size_t KibiByte = 1024;

	class MemoryManager
	{
	private:
		/// <summary>
		/// SharedMutex for concurrent read access and exclusive write access
		/// </summary>
		static std::shared_mutex _sharedMutex;

		/// <summary>
		/// A pool of memory that is created at initialization of this class, relied upon by other subsystems for dynamic memory allocation through this manager
		/// </summary>
		void* m_systemMemory = nullptr;

		/// <summary>
		/// Allocator used to partition the systemMemory and divy it up to the MemoryMap instances PageAllocators
		/// </summary>
		VMFramework::StackAllocator* m_systemAllocator = nullptr;

		/// <summary>
		/// Pointer the the instance of this singleton that is created when GetInstance is called
		/// </summary>
		static MemoryManager* s_instance;

		/// <summary>
		/// A reference to a MemoryMap instance that will be used by the MemoryManager for paging and address translation
		/// </summary>
		MemoryMap* const& m_memoryMap = nullptr;

		/// <summary>
		/// Default constructor is private, MemoryManager is a singleton. Internal use only
		/// </summary>
		MemoryManager();
		
		/// <summary>
		/// Default destructor is private, MemoryManager is a singleton. Internal use only
		/// </summary>
		~MemoryManager();

	public:
		/// <summary>
		/// Get a pointer to the singletons active instance, or makes an instance if there isn't one already
		/// </summary>
		/// <returns>Pointer to the MemoryManager instance</returns>
		static MemoryManager* GetInstance();

		/// <summary>
		/// Launch the MemoryManager sub-system and configure with provided parameters
		/// </summary>
		/// <param name="systemBytes"></param>
		/// <param name="memoryMap"></param>
		void StartUp(const size_t& systemBytes, MemoryMap& memoryMap);
		
		/// <summary>
		/// Release the sub-systems resources and safely destroy it
		/// </summary>
		void ShutDown();

		/// <summary>
		/// Used to create a new page worth of memory in the callers address space
		/// </summary>
		/// <param name="pageType">The id of the kind of page to allocate. Avalable kinds dependant on configured MemoryMap implementation</param>
		/// <returns>Pointer to the page allocated in system memory</returns>
		inline void* AllocateUserPage(const uint8_t& pageType)
		{
			return m_memoryMap->AllocateUserPage(pageType);
		}

		/// <summary>
		/// Used to create a new page worth of memory in the systems/kernels address space
		/// </summary>
		/// <param name="pageType">The id of the kind of page to allocate. Avalable kinds dependant on configuration of MemoryMap implementation</param>
		/// <returns>Pointer to the page allocated in system memory</returns>
		inline void* AllocateKernelPage(const uint8_t& pageType)
		{
			return m_memoryMap->AllocateUserPage(pageType);
		}

		/// <summary>
		/// Used to create the pages needed to satisfy the requested memory amount in the callers address space
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested in bytes</param>
		/// <returns>Pointer to the first of the pages allocated in system memory to satisfy the memory request</returns>
		inline void* AllocateUserPagesFor(const size_t& bytesNeeded)
		{
			return m_memoryMap->AllocateUserPagesFor(bytesNeeded);
		}

		/// <summary>
		/// Used to create the pages needed to satisfy the requested memory amount in the systems/kernels address space
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested in bytes</param>
		/// <returns>Pointer to the first of the pages allocated in system memory to satisfy the memory request</returns>
		inline void* AllocateKernelPagesFor(const size_t& bytesNeeded)
		{
			return m_memoryMap->AllocateKernelPagesFor(bytesNeeded);
		}

		/// <summary>
		/// Used to translate a virtual address/pointer in a callers address space into the systems/physical memory address space
		/// </summary>
		/// <typeparam name="SystemPtr">The type used by the underlying machine for its virtual addresses</typeparam>
		/// <param name="virtualAddress">The virtual address to be translated/mapped into its associated physical address in system memory</param>
		/// <returns>Pointer to the location in memory the provided virtual address maps to</returns>
		template<std::unsigned_integral SystemPtr>
		inline void* Virtual_To_Physical(const SystemPtr& virtualAddress)
		{
			return m_memoryMap->Virtual_To_Physical<SystemPtr>(virtualAddress);
		}

		/// <summary>
		/// Used to translate an address/pointer in system/physical address space into the virtual address space of the caller
		/// </summary>
		/// <typeparam name="SystemPtr">The type used by the underlying machine for its virtual addresses</typeparam>
		/// <param name="physicalAddress">The system/physical address to be translated/mapped into its associated virtual address in the caller's address space</param>
		/// <returns>Virtual address in the callers address sapace associated with the provided system pointer</returns>
		template<std::unsigned_integral SystemPtr>
		inline SystemPtr Physical_To_Virtual(const void* const& physicalAddress)
		{
			return m_memoryMap->Physical_To_Virtual<SystemPtr>(physicalAddress);
		}

		//Do not attempt to copy, manager is a singleton
		MemoryManager(const MemoryManager&) = delete;
		//Do not attempt to copy, manager is a singleton
		MemoryManager& operator=(const MemoryManager&) = delete;
		//Do not attempt to move, manager is a singleton. Undefined behavior
		MemoryManager(MemoryManager&&) = delete;
		//Do not attempt to move, manager is a singleton. Undefined behavior
		MemoryManager& operator=(MemoryManager&&) = delete;
	};
}
#endif //!MEMORY_MANAGER_H
