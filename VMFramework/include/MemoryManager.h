#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <cstdint>
#include <thread>
#include <shared_mutex>

#include "StackAllocator.h"

#define TOTAL_GIBIGYTES_FOR_SYSTEM 1

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
		void* m_ApplicationMemory = nullptr;

		/// <summary>
		/// Pointer the the instance of this singleton that is created when GetInstance is called
		/// </summary>
		static MemoryManager* s_instance;

		/// <summary>
		/// Default constructor is private, MemoryManager is a singleton. Internal use only
		/// </summary>
		MemoryManager();
		
		/// <summary>
		/// Default destructor is private, MemoryManager is a singleton. Internal use only
		/// </summary>
		~MemoryManager();

	public:
		VMFramework::StackAllocator* m_systemAllocator = nullptr;

		static MemoryManager* GetInstance();

		void StartUp();
		void ShutDown();

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
