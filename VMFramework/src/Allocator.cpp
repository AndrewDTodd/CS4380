#include "../include/Allocator.h"

#include <cassert>
#include <stdexcept>
#include <type_traits>

namespace VMFramework
{
	Allocator::Allocator(const size_t& size, void* start) : m_size(size), m_start(start)
	{
#ifdef _DEBUG
		if (start == nullptr)
			throw std::invalid_argument("Start of Allocator can not be nullptr");
#endif // _DEBUG
	}

	Allocator::~Allocator()
#ifdef _DEBUG
		noexcept(false)
#endif // _DEBUG
	{
		m_start = nullptr;
		m_size = 0;

#ifdef _DEBUG
		if (m_numOfAllocations != 0 || m_usedMemory != 0)
			throw std::runtime_error("Destroying the Allocator before all allocations have been freed results in memory leak. Ensure all allocations have been deallocated");
#endif // _DEBUG
	}

	void Allocator::ClearAllocator()
	{
		m_numOfAllocations = 0;
		m_usedMemory = 0;
	}

	void* Allocator::GetStart() const
	{
		return m_start;
	}

	size_t Allocator::GetSize() const
	{
		return m_size;
	}

	size_t Allocator::GetUsedMemory() const
	{
		return m_usedMemory;
	}

	size_t Allocator::GetNumOfAllocations() const
	{
		return m_numOfAllocations;
	}
}