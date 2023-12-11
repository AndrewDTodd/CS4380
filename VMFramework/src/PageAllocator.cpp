#include "../include/PageAllocator.h"

#include <cassert>
#include "MemoryManager.h"

namespace VMFramework
{
	PageAllocator::PageAllocator(const size_t& size, void* start) : Allocator(size, start), m_currentPosition(start)
	{
		assert(size > 0);
	}

	PageAllocator::~PageAllocator()
	{
		m_currentPosition = nullptr;
	}

	void PageAllocator::Clear()
	{
		m_numOfAllocations = 0;
		m_usedMemory = 0;

		m_currentPosition = m_start;
	}
}