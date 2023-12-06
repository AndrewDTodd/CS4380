#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
//#include <execution>
#include <stdexcept>

#include "Allocator.h"

namespace VMFramework
{
	class stack_overflow : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Stack Overflow detected: Not enough memory remaining for requested allocation";
		}
	};

	/// <summary>
	/// StackAllocator works by allocating segments of memory that are "pushed" onto the allocators block of memory when an allocation is made, and "popped" off when a deallocation is made
	/// </summary>
	class StackAllocator : public Allocator
	{
	private:
		struct AllocationHeader
		{
#if _DEBUG
			void* m_prev_address = nullptr;
#endif //_DEBUG

			uint8_t m_adjustment;
		};

#ifdef _DEBUG
		void* m_prev_position = nullptr;
#endif //_DEBUG

		void* m_current_position = nullptr;

	public:
		/// <summary>
		/// Construct an instance of StackAllocator with specified configuration
		/// </summary>
		/// <param name="size">Number of bytes for this allocator to control</param>
		/// <param name="start">Begining of the bytes for this allocator</param>
		StackAllocator(const size_t& size, void* start);
		~StackAllocator();

		/// <inheritdoc/>
		void* Allocate(const size_t& size, const uint8_t& alignment) override;

		/// <inheritdoc/>
		void Deallocate(void* address) override;

		void ClearAllocator() override;

		StackAllocator(const StackAllocator&) = delete;
		StackAllocator& operator=(const StackAllocator&) = delete;
		StackAllocator(StackAllocator&&) = delete;
		StackAllocator& operator=(StackAllocator&&) = delete;
	};
}
#endif //!STACK_ALLOCATOR_H
