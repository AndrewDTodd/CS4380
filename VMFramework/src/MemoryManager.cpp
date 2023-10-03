#include "../include/MemoryManager.h"

#include <cstdint>
#include <new>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <stdexcept>

#include "../include/StackAllocator.h"

#define MUL(a,b) ((a) * (b))

namespace VMFramework
{
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
		std::shared_lock<std::shared_mutex> readLock(MemoryManager::_sharedMutex);

		if (!MemoryManager::s_instance)
		{
			std::unique_lock<std::shared_mutex> writeLock(MemoryManager::_sharedMutex);

			if (!MemoryManager::s_instance)
			{
				
				MemoryManager::s_instance = new MemoryManager();
				return MemoryManager::s_instance;
			}
		}
			return MemoryManager::s_instance;
	}

	void MemoryManager::StartUp()
	{
		std::unique_lock<std::shared_mutex> writeLock(MemoryManager::_sharedMutex);

#ifdef _DEBUG
		if (this->m_ApplicationMemory != nullptr)
			throw std::runtime_error("Calling StartUp on an already active MemoryManager is invalid");
#endif // _DEBUG

		this->m_ApplicationMemory = malloc(MUL(GibiByte, TOTAL_GIBIGYTES_FOR_SYSTEM));

		this->m_systemAllocator = new (this->m_ApplicationMemory) StackAllocator(MUL(GibiByte, TOTAL_GIBIGYTES_FOR_SYSTEM), PointerMath::Add(this->m_ApplicationMemory, sizeof(StackAllocator)));
	}

	void MemoryManager::ShutDown()
	{
		std::unique_lock<std::shared_mutex> writeLock(MemoryManager::_sharedMutex);

		this->m_systemAllocator->~StackAllocator();
		this->m_systemAllocator = nullptr;
		free(this->m_ApplicationMemory);
		this->m_ApplicationMemory = nullptr;

		this->~MemoryManager();
	}
}