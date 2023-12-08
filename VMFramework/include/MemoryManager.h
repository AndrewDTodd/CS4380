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
	constexpr uint64_t GibiByte = 1073741824;
	constexpr uint64_t MebiByte = 1048576;
	constexpr uint64_t KibiByte = 1024;

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
		static MemoryManager* GetInstance();

		void StartUp(const size_t& systemBytes, MemoryMap& memoryMap);
		void ShutDown();

		void* AllocatePage(const uint8_t& pageType);

		template<std::unsigned_integral SystemPtr>
		inline void* Virtual_To_Physical(const SystemPtr& virtualAddress)
		{
			return m_memoryMap.Virtual_To_Physical<SystemPtr>(virtualAddress);
		}

		template<std::unsigned_integral SystemPtr>
		inline SystemPtr Physical_To_Virtual(const void* const& physicalAddress)
		{
			return m_memoryMap.Physical_To_Virtual<SystemPtr>(physicalAddress);
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
