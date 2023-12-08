#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <cstdint>
#include <cstddef>

#include "PageAllocator.h"

namespace VMFramework
{
	class out_of_memory : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Page Allocator is out of memory";
		}
	};

	/*template<typename T>
	concept DerivedFromPageAllocator = std::derived_from<T, PageAllocator>;*/

	class MemoryMap
	{
	protected:
		const uint8_t* const& m_normalPagePhysicalAddressOrdinal;
		//const size_t m_userSpaceBytes;
		PageAllocator** m_pageAllocators = nullptr;
		const size_t m_numPageAllocators;

		MemoryMap() = default;
		~MemoryMap();

		void SetPageAllocators(const PageAllocator* pageAllocators...);

	public:
		virtual void Initialize(const size_t& systemBytes, Allocator* const& systemAllocator) = 0;

		virtual void* AllocatePage(const uint8_t& pageType) = 0;

		template<std::unsigned_integral SystemPtr>
		inline void* Virtual_To_Physical(const SystemPtr& virtualAddress) {};

		template<std::unsigned_integral SystemPtr>
		inline SystemPtr Physical_To_Virtual(const void* const& physicalAddress) {};
	};
}
#endif // !MEMORY_MAP_H
