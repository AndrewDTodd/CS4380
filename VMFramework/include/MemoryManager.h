#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <cstdint>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <concepts>

#include "LinearAllocator.h"
#include "MemoryMap.h"

//#define TOTAL_GIBIGYTES_FOR_SYSTEM 1

namespace VMFramework
{
	constexpr size_t GibiByte = 1073741824;
	constexpr size_t MebiByte = 1048576;
	constexpr size_t KibiByte = 1024;

	template<std::integral RegisterType>
	class MemoryManager
	{
	private:
		/// <summary>
		/// SharedMutex for concurrent read access and exclusive write access
		/// </summary>
		inline static std::shared_mutex _sharedMutex;

		/// <summary>
		/// A pool of memory that is created at initialization of this class, relied upon by other subsystems for dynamic memory allocation through this manager
		/// </summary>
		void* m_systemMemory = nullptr;

		/// <summary>
		/// Allocator used to partition the systemMemory and divy it up to the MemoryMap instances PageAllocators
		/// </summary>
		VMFramework::LinearAllocator* m_systemAllocator = nullptr;

		/// <summary>
		/// Pointer the the instance of this singleton that is created when GetInstance is called
		/// </summary>
		inline static MemoryManager<RegisterType>* s_instance = nullptr;

		/// <summary>
		/// A reference to a MemoryMap instance that will be used by the MemoryManager for paging and address translation
		/// </summary>
		MemoryMap<RegisterType>* m_memoryMap = nullptr;

		/// <summary>
		/// Default constructor is private, MemoryManager is a singleton. Internal use only
		/// </summary>
		MemoryManager()
		{}
		
		/// <summary>
		/// Default destructor is private, MemoryManager is a singleton. Internal use only
		/// </summary>
		~MemoryManager()
		{}

	public:
		/// <summary>
		/// Get a pointer to the singletons active instance, or makes an instance if there isn't one already
		/// </summary>
		/// <returns>Pointer to the MemoryManager instance</returns>
		static MemoryManager<RegisterType>* GetInstance()
		{
			//Acquire concurrent read lock for read access
			std::shared_lock<std::shared_mutex> readLock(_sharedMutex);

			if (!MemoryManager::s_instance)
			{
				//Release the read lock to prevent deadlock
				readLock.unlock();
				//Acquire exclusive lock for write
				std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

				if (!MemoryManager::s_instance)
				{
					MemoryManager::s_instance = new MemoryManager();
					return MemoryManager::s_instance;
				}
			}
			return MemoryManager::s_instance;
		}

		/// <summary>
		/// Launch the MemoryManager sub-system and configure with provided parameters
		/// </summary>
		/// <param name="systemBytes"></param>
		/// <param name="memoryMap"></param>
		void StartUp(const size_t& systemBytes, MemoryMap<RegisterType>& memoryMap)
		{
			//Acquire exclusive lock for write
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

#ifdef _DEBUG
			if (this->m_systemMemory != nullptr)
				throw std::runtime_error("Calling StartUp on an already active MemoryManager is invalid");
#endif // _DEBUG

			this->m_systemMemory = malloc(systemBytes);

			this->m_systemAllocator = new (this->m_systemMemory) LinearAllocator(systemBytes - sizeof(LinearAllocator), PointerMath::Add(this->m_systemMemory, sizeof(LinearAllocator)));

			m_memoryMap = &memoryMap;

			m_memoryMap->Initialize(m_systemAllocator->GetSize(), m_systemAllocator);
		}
		
		/// <summary>
		/// Release the sub-systems resources and safely destroy it
		/// </summary>
		void ShutDown()
		{
			std::unique_lock<std::shared_mutex> writeLock(_sharedMutex);

#ifdef _DEBUG
			if (!this->m_systemMemory)
				throw std::runtime_error("Calling ShutDown on an inactive MemoryManager is invalid");
#endif // _DEBUG
			
			this->m_memoryMap->ShutDown();

			this->m_systemAllocator->Clear();
			this->m_systemAllocator->~LinearAllocator();
			this->m_systemAllocator = nullptr;
			free(this->m_systemMemory);
			this->m_systemMemory = nullptr;

			this->~MemoryManager();
		}

		/// <summary>
		/// Used to create a new page worth of memory in the callers address space
		/// </summary>
		/// <param name="pageType">The id of the kind of page to allocate. Avalable kinds dependant on configured MemoryMap implementation</param>
		/// <returns>Pointer to the page allocated in system memory</returns>
		inline void* AllocateUserPage(const uint8_t& pageType, const bool& pageWritable = MemoryMap<RegisterType>::PageReadWrite::read_write)
		{
			return m_memoryMap->AllocateUserPage(pageType, pageWritable);
		}

		/// <summary>
		/// Used to create a new page worth of memory in the systems/kernels address space
		/// </summary>
		/// <param name="pageType">The id of the kind of page to allocate. Avalable kinds dependant on configuration of MemoryMap implementation</param>
		/// <returns>Pointer to the page allocated in system memory</returns>
		inline void* AllocateKernelPage(const uint8_t& pageType, const bool& pageWritable = MemoryMap<RegisterType>::PageReadWrite::readonly)
		{
			return m_memoryMap->AllocateUserPage(pageType, pageWritable);
		}

		/// <summary>
		/// Used to create the pages needed to satisfy the requested memory amount in the callers address space
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested in bytes</param>
		/// <returns>Pointer to the first of the pages allocated in system memory to satisfy the memory request</returns>
		inline void* AllocateUserPagesFor(const size_t& bytesNeeded, const bool& pageWritable = MemoryMap<RegisterType>::PageReadWrite::read_write)
		{
			return m_memoryMap->AllocateUserPagesFor(bytesNeeded, pageWritable);
		}

		/// <summary>
		/// Used to create the pages needed to satisfy the requested memory amount in the systems/kernels address space
		/// </summary>
		/// <param name="bytesNeeded">The amount of memory requested in bytes</param>
		/// <returns>Pointer to the first of the pages allocated in system memory to satisfy the memory request</returns>
		inline void* AllocateKernelPagesFor(const size_t& bytesNeeded, const bool& pageWritable = MemoryMap<RegisterType>::PageReadWrite::readonly)
		{
			return m_memoryMap->AllocateKernelPagesFor(bytesNeeded, pageWritable);
		}

		/// <summary>
		/// Used to free an allocation made by a process
		/// </summary>
		/// <param name="pagesStart">Poiner to the first byte of the first page in the sequence of pages to be freed</param>
		/// <param name="pagesBytes">The number of bytes that was allocated and will now be freed. The total size of the pages to free</param>
		inline void FreePages(void* pagesStart, const size_t& pagesBytes)
		{
			return m_memoryMap->FreePages(pagesStart, pagesBytes);
		}

		/// <summary>
		/// Used to translate a virtual address/pointer in a callers address space into the systems/physical memory address space
		/// </summary>
		/// <param name="virtualAddress">The virtual address to be translated/mapped into its associated physical address in system memory</param>
		/// <returns>Pointer to the location in memory the provided virtual address maps to</returns>
		inline void* Virtual_To_Physical(const RegisterType& virtualAddress)
		{
			return m_memoryMap->Virtual_To_Physical(virtualAddress);
		}

		/// <summary>
		/// Used to translate an address/pointer in system/physical address space into the virtual address space of the caller
		/// </summary>
		/// <param name="physicalAddress">The system/physical address to be translated/mapped into its associated virtual address in the caller's address space</param>
		/// <returns>Virtual address in the callers address sapace associated with the provided system pointer</returns>
		inline RegisterType Physical_To_Virtual(const void* const& physicalAddress)
		{
			return m_memoryMap->Physical_To_Virtual(physicalAddress);
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
