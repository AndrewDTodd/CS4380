#include "../include/MemoryManager.h"

#include <cstdint>
#include <new>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <stdexcept>
#include <type_traits>

#include "../include/StackAllocator.h"

#define MUL(a,b) ((a) * (b))

namespace VMFramework
{
	//Initialize the static members of MemoryManager
	MemoryManager* MemoryManager::s_instance = nullptr;
	std::shared_mutex MemoryManager::_sharedMutex;

	MemoryManager::MemoryManager()
	{
	}
	MemoryManager::~MemoryManager()
	{
	}

	MemoryManager* MemoryManager::GetInstance()
	{
		//Acquire concurrent read lock for read access
		std::shared_lock<std::shared_mutex> readLock(MemoryManager::_sharedMutex);

		if (!MemoryManager::s_instance)
		{
			//Release the read lock to prevent deadlock
			readLock.unlock();
			//Acquire exclusive lock for write
			std::unique_lock<std::shared_mutex> writeLock(MemoryManager::_sharedMutex);

			if (!MemoryManager::s_instance)
			{
				MemoryManager::s_instance = new MemoryManager();
				return MemoryManager::s_instance;
			}
		}
			return MemoryManager::s_instance;
	}

	void MemoryManager::StartUp(const size_t& systemBytes, MemoryMap& memoryMap)
	{
		//Acquire exclusive lock for write
		std::unique_lock<std::shared_mutex> writeLock(MemoryManager::_sharedMutex);

#ifdef _DEBUG
		if (this->m_systemMemory != nullptr)
			throw std::runtime_error("Calling StartUp on an already active MemoryManager is invalid");
#endif // _DEBUG

		this->m_systemMemory = malloc(systemBytes);

		this->m_systemAllocator = new (this->m_systemMemory) StackAllocator(systemBytes - sizeof(StackAllocator), PointerMath::Add(this->m_systemMemory, sizeof(StackAllocator)));

		const_cast<MemoryMap*&>(m_memoryMap) = &memoryMap;

		m_memoryMap->Initialize(m_systemAllocator->GetSize(), m_systemAllocator);
	}

	void MemoryManager::ShutDown()
	{
		std::unique_lock<std::shared_mutex> writeLock(MemoryManager::_sharedMutex);

#ifdef _DEBUG
		if (!this->m_systemMemory)
			throw std::runtime_error("Calling ShutDown on an inactive MemoryManager is invalid");
#endif // _DEBUG

		this->m_systemAllocator->~StackAllocator();
		this->m_systemAllocator = nullptr;
		free(this->m_systemMemory);
		this->m_systemMemory = nullptr;

		this->~MemoryManager();
	}

	void* MemoryManager::AllocatePage(const uint8_t& pageType)
	{
		m_memoryMap->AllocatePage(pageType);
	}
}