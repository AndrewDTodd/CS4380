#include "../include/LinearAllocator.h"

#include <cassert>

namespace VMFramework
{
	LinearAllocator::LinearAllocator(const size_t& size, void* start): Allocator(size, start), m_currentPosition(start)
	{
		assert(size > 0);
	}

	LinearAllocator::~LinearAllocator()
	{
		m_currentPosition = nullptr;
	}

	void* LinearAllocator::Allocate(const size_t& size, const uint8_t& alignment)
	{
		assert(size > 0);

		uint8_t adjustment = PointerMath::AlignForwardAdjustment(m_currentPosition, alignment);

		if (m_usedMemory + adjustment + size > m_size)
			return nullptr;

		void* aligned_address = PointerMath::Add(m_currentPosition, adjustment);

		m_currentPosition = PointerMath::Add(aligned_address, size);

		m_usedMemory += size + adjustment;

		m_numOfAllocations++;

		return aligned_address;
	}

	void LinearAllocator::Deallocate(void*)
	{
		static_assert("Use Clear() instead");
	}

	void LinearAllocator::Clear()
	{
		m_numOfAllocations = 0;
		m_usedMemory = 0;

		m_currentPosition = m_start;
	}
}