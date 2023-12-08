#include "../include/MemoryMap.h"

#include <stdexcept>
#include <string>
#include <type_traits>

namespace VMFramework
{
	MemoryMap::~MemoryMap()
	{
		delete[] m_pageAllocators;
	}

	MemoryMap::~MemoryMap()
	{
		delete[] m_pageAllocators;
	}

	void MemoryMap::SetPageAllocators(const PageAllocator* pageAllocators...)
	{
		constexpr size_t numAllocators = sizeof...(pageAllocators);
		const_cast<size_t>&(m_numPageAllocators) = numAllocators;

		const_cast<PageAllocator**>&(m_pageAllocators) = new PageAllocator* [](numAllocators) {pageAllocators...};
	}
}