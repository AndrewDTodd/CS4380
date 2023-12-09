#include "../include/MemoryMap.h"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <cassert>

namespace VMFramework
{
	MemoryMap::~MemoryMap()
	{
		delete[] m_pageAllocators;
	}

	template<PageAllocatorType... Page_Allocators>
	void MemoryMap::SetPageAllocators(Page_Allocators*... pageAllocators)
	{
#ifdef _DEBUG
		assert(m_pageAllocators == nullptr);
#endif // _DEBUG

		constexpr size_t numAllocators = sizeof...(pageAllocators);
		const_cast<size_t>(m_numPageAllocators) = numAllocators;

		m_pageAllocators = new PageAllocator* [numAllocators]{pageAllocators...};
	}
}