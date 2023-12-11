#include "../include/MemoryMap.h"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <cassert>

namespace VMFramework
{
	MemoryMap::MemoryMap()
	{}

	MemoryMap::~MemoryMap()
	{
		for (size_t pageAllocator = 0; pageAllocator < m_numPageAllocators; pageAllocator++)
		{
			m_pageAllocators[pageAllocator]->Clear();
			m_pageAllocators[pageAllocator]->ClearAllocator();
		}

		delete[] m_pageAllocators;
	}
}