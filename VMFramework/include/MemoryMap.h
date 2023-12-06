#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <cstdint>
#include <concepts>
#include <cstddef>
#include <unordered_set>
#include <type_traits>

#include "PageAllocator.h"

namespace VMFramework
{
	template<typename T>
	concept DerivedFromPageAllocator = std::derived_from<T, PageAllocator>;

	class MemoryMap
	{
	protected:
		const uint8_t* const& m_physicalAddressOrdinal;
		const size_t m_userSpaceBytes;
		PageAllocator** m_pageAllocators = nullptr;
		const size_t m_numPageAllocators;

		virtual void Initialize(const size_t& systemBytes) = 0;

		void SetPageAllocators(const DerivedFromPageAllocator auto&... pageAllocators)
		{
			constexpr size_t numAllocators = sizeof...(pageAllocators);
			std::remove_const(m_numPageAllocators) = numAllocators;

			std::remove_const(m_pageAllocators) = new PageAllocator*[numAllocators]{std::forward<DerivedFromPageAllocator>(pageAllocators)...};
		}

		void* AllocatePage(const uint8_t& pageType);

		template<std::unsigned_integral SystemPtr>
		void* Virtual_To_Physical(const SystemPtr& virtualAddress) {};

		template<std::unsigned_integral SystemPtr>
		SystemPtr Physical_To_Virtual(const void* const& physicalAddress) {};

		MemoryMap() = default;
		~MemoryMap();
	};
}
#endif // !MEMORY_MAP_H
