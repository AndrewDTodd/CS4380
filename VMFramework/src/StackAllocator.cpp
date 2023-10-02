#include "../include/StackAllocator.h"

#include <cstdint>
#include <cstddef>
#include <cassert>

namespace VMFramework
{
	StackAllocator::StackAllocator(const size_t& size, void* start) : Allocator(size, start), m_current_position(start)
	{
		assert(size > 0);
	}

	StackAllocator::~StackAllocator()
	{
#ifdef _DEBUG
		m_prev_position = nullptr;
#endif // _DEBUG

		m_current_position = nullptr;
	}

	void* StackAllocator::Allocate(const size_t& size, const uint8_t& alignment)
	{
		assert(size != 0);

		uint8_t adjustment = PointerMath::AlignForwardAdjustmentWithHeader(m_current_position, alignment, sizeof(AllocationHeader));

		if (m_usedMemory + adjustment + size > m_size)
			throw stack_overflow();

		void* aligned_address = PointerMath::Add(m_current_position, adjustment);

		//Add Allocation Header
		AllocationHeader* header = (AllocationHeader*)(PointerMath::Subtract(aligned_address, sizeof(AllocationHeader)));

		header->m_adjustment = adjustment;

#ifdef _DEBUG
		header->m_prev_address = m_prev_position;

		m_prev_position = aligned_address;
#endif // _DEBUG

		m_current_position = PointerMath::Add(aligned_address, size);

		m_usedMemory += size + adjustment;

		m_numOfAllocations++;

		return aligned_address;
	}

	void StackAllocator::Deallocate(void* p)
	{
#ifdef _DEBUG
		assert(p == m_prev_position);
#endif // _DEBUG

		//Access the AllocationHeader in the bytes before p
		AllocationHeader* header = (AllocationHeader*)(PointerMath::Subtract(p, sizeof(AllocationHeader)));

		m_usedMemory -= (uintptr_t)m_current_position - (uintptr_t)p + header->m_adjustment;

		m_current_position = PointerMath::Subtract(p, header->m_adjustment);

#ifdef _DEBUG
		m_prev_position = header->m_prev_address;
#endif // _DEBUG

		m_numOfAllocations--;
	}

	void StackAllocator::ClearAllocator()
	{
		Allocator::ClearAllocator();

		m_current_position = m_start;

#ifdef _DEBUG
		m_prev_position = nullptr;
#endif // _DEBUG
	}
}