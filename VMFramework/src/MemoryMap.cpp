#include "../include/MemoryMap.h"

#include <stdexcept>
#include <string>

namespace VMFramework
{
	MemoryMap::~MemoryMap()
	{
		delete[] m_pageAllocators;
	}

	void* MemoryMap::AllocatePage(const uint8_t& pageType)
	{
#ifdef _DEBUG
		if (pageType > m_numPageAllocators - 1)
			throw std::invalid_argument("There is no page type with id: " + std::to_string(pageType));
#endif // _DEBUG

		m_pageAllocators[pageType]->Allocate();
	}
}