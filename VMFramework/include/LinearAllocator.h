#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include <stdexcept>

#include "Allocator.h"

namespace VMFramework
{
	class LinearAllocator : public Allocator
	{
	private:
		void* m_currentPosition = nullptr;

		void Deallocate(void*) override;
	public:
		LinearAllocator(const size_t& size, void* start);
		~LinearAllocator();

		void* Allocate(const size_t& size, const uint8_t& alignment) override;
		void Clear();

		LinearAllocator(const LinearAllocator&) = delete;
		LinearAllocator& operator=(const LinearAllocator&) = delete;
		LinearAllocator(LinearAllocator&&) = delete;
		LinearAllocator& operator=(LinearAllocator&&) = delete;
	};
}
#endif // !LINEAR_ALLOCATOR_H
