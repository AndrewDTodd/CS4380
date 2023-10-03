#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <cstdint>
#include <cassert>
#include <new>

namespace VMFramework
{
	class PointerMath
	{
	public:
		static void* AlignForward(void* address, const uint8_t& alignment);
		static const void* AlignForward(const void* address, const uint8_t& alignment);

		static void* AlignBackward(void* address, const uint8_t& alignment);
		static const void* AlignBackward(const void* address, const uint8_t& alignment);

		static uint8_t     AlignForwardAdjustment(const void* address, const uint8_t& alignment);
		static uint8_t     AlignForwardAdjustmentWithHeader(const void* address, const uint8_t& alignment, const uint8_t& headerSize);

		static uint8_t     AlignBackwardAdjustment(const void* address, const uint8_t& alignment);

		static void* Add(void* p, const size_t& x);
		static const void* Add(const void* p, const size_t& x);

		static void* Subtract(void* p, const size_t& x);
		static const void* Subtract(const void* p, const size_t& x);

		//Class is static, do not attempt to make instance
		PointerMath() = delete;
		~PointerMath() = delete;
		PointerMath(const PointerMath&) = delete;
		PointerMath& operator=(const PointerMath&) = delete;
		PointerMath(PointerMath&&) = delete;
		PointerMath& operator=(PointerMath&&) = delete;
	};

	/// <summary>
	/// Allocator base class is used to define specific types of memory allocators for different use cases
	/// </summary>
	class Allocator
	{
	protected:
		/// <summary>
		/// The address at the begining of this allocators controlled memory block
		/// </summary>
		void* m_start;

		/// <summary>
		/// The number of bytes that have been used in this allocator's block of memory
		/// </summary>
		size_t m_usedMemory = 0;

		/// <summary>
		/// The number of individual allocations from this allocator's block of memeory that are active
		/// </summary>
		size_t m_numOfAllocations = 0;

		/// <summary>
		/// Create an allocator instance with the specified configuration
		/// </summary>
		/// <param name="size">The number of bytes this allocator should claim for its block</param>
		/// <param name="start">The address where this allocators block will begin</param>
		/// <exeption cref="invalid_argument">Thrown if start is nullptr</exeption>
		Allocator(const size_t& size, void* start);

		/// <summary>
		/// Base class destructor, will set Allocators pointers and members to default value
		/// </summary>
		/// <exeption cref="runtime_error">Thrown in Debug builds if the number of allocations or the used memory size are not 0, indicating a memory leak</exeption>
		virtual ~Allocator()
#ifdef _DEBUG
			noexcept(false)
#endif // _DEBUG
			;

	public:
		/// <summary>
		/// The number of bytes in this allocators block of memory (total)
		/// </summary>
		size_t m_size;

		/// <summary>
		/// Make an allocation on this allocator's block of memory
		/// </summary>
		/// <param name="size">The number of bytes to claim</param>
		/// <param name="allignment">The alignment needed for the allocation, default is 8 byte allign</param>
		/// <returns>A pointer to first byte of the allocation</returns>
		virtual void* Allocate(const size_t& size, const uint8_t& allignment = 8) = 0;

		/// <summary>
		/// Free up an allocation that was made on this allocator's block of memory
		/// </summary>
		/// <param name="address">The first byte in the allocation that is to be freed</param>
		virtual void Deallocate(void* address) = 0;

		/// <summary>
		/// Clear the Allocator and reset it to it's initial state. Effectively remove all allocations, which may invalidate existing pointers
		/// </summary>
		virtual void ClearAllocator();

		/// <summary>
		/// Gets the address of the first byte in this allocator's block of memory
		/// </summary>
		/// <returns>Address of the block's first byte</returns>
		void* GetStart() const;

		/// <summary>
		/// Gets the number of bytes in this allocator's block of memory
		/// </summary>
		/// <returns></returns>
		size_t GetSize() const;

		/// <summary>
		/// Gets the number of bytes presently in use in the allocator's block of memory
		/// </summary>
		/// <returns>Number of bytes currently used</returns>
		size_t GetUsedMemory() const;

		/// <summary>
		/// Gets the number of active allocations made from this allocator
		/// </summary>
		/// <returns>Number of active allocations</returns>
		size_t GetNumOfAllocations() const;
	};

	//Template functions used by Allocators

	/// <summary>
	/// Will create a new instance of the Type using the memory in the passed Allocator
	/// </summary>
	/// <typeparam name="T">The type to allocate</typeparam>
	/// <param name="size">The number of bytes needed to create instance of T</param>
	/// <param name="allocator">Pointer to Allocator instance to get memory from</param>
	/// <returns>Pointer to the allocated instance</returns>
	template <class T> T* AllocateNew(const size_t& size, Allocator* allocator)
	{
		void* p = allocator->Allocate(size + sizeof(T), __alignof(T));
		return new (p) T(size, PointerMath::Add(p, sizeof(T)));
	}

	/// <summary>
	/// Will create a new instance of the Type using the memory in the passed Allocator
	/// </summary>
	/// <typeparam name="T">The type to allocate</typeparam>
	/// <param name="size">The number of bytes needed to create instance of T</param>
	/// <param name="allocator">Reference to Allocator instance to get memory from</param>
	/// <returns>Pointer to the allocated instance</returns>
	template <class T> T* AllocateNew(const size_t& size, Allocator& allocator, const T& t)
	{
		return new (allocator.Allocate(sizeof(T), __alignof(T))) T(t);
	}

	/// <summary>
	/// Will free the memory used by the instance in the allocator and delete the instance of T
	/// </summary>
	/// <typeparam name="T">The type that is being deallocated</typeparam>
	/// <param name="allocator">Reference to Allocator whos memory is being freed</param>
	/// <param name="object">Reference to the instance who is being released and deleted</param>
	template<class T> void DeallocateDelete(Allocator& allocator, T& object)
	{
		object.~T();
		allocator.Deallocate(&object);
	}

	/// <summary>
	/// Will allocate the memory needed for an array of T in the specified Allocator
	/// </summary>
	/// <typeparam name="T">The type to allocate instances of to make array</typeparam>
	/// <param name="allocator">Pointer to allocator to retrieve needed memory from</param>
	/// <param name="length">The number of instances of T to make</param>
	/// <returns>Pointer to begining of the allocated array</returns>
	template<class T> T* AllocateArray(Allocator* allocator, const size_t& length)
	{
		assert(length != 0 && "Cannot allocate an array with legth of 0");

		uint8_t headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		T* p = nullptr;

		//Allocate extra space to store array length in the bytes before the array
		p = ((T*)allocator->Allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;

		//Store the length in the header
		*(((size_t*)p) - 1) = length;

		//Create instances of T using the placement new operator, placing the instances in the block from the allocation
		for (size_t i = 0; i < length; i++)
			new (&p[i]) T;

		//Return pointer to the begining of the array (not the header)
		return p;
	}

	/// <summary>
	/// Will allocate the memory needed for an array of T in the specified Allocator and initialize the elements by move constructing them with the passed rvalue instace of T
	/// </summary>
	/// <typeparam name="T">The type to allocate instances of to make array</typeparam>
	/// <param name="allocator">Pointer to allocator to retrieve needed memory from</param>
	/// <param name="length">The number of instances of T to make</param>
	/// <param name="t">An rvalue reference to an instance of T to use for constructing the elements of the array</param>
	/// <returns>Pointer to begining of the allocated array</returns>
	template<class T> T* AllocateArray(Allocator* allocator, const size_t& length, T&& t)
	{
		assert(length != 0 && "Cannot allocate an array with legth of 0");

		uint8_t headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		T* p = nullptr;

		//Allocate extra space to store array length in the bytes before the array
		p = ((T*)allocator->Allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;

		//Store the length of the array in the header
		*(((size_t*)p) - 1) = length;

		//Create instances of T using the placement new operator and the move constructor of T, placing the instances in the block from the allocation
		for (size_t i = 0; i < length; i++)
		{
			new (&p[i]) T(t);
		}

		//Return pointer to the begining of the array (not the header)
		return p;
	}

	/// <summary>
	/// Will free the memory used by the specified array in the specified Allocator
	/// </summary>
	/// <typeparam name="T">The type of the elements of the array</typeparam>
	/// <param name="allocator">Pointer to the allocator whos memory is to be freed</param>
	/// <param name="array">Pointer to the array of T that is to be deallocated</param>
	template<class T> void DeallocateArray(Allocator* allocator, T* array)
	{
		assert(array != nullptr && "Cannot deallocate a non existant array, nullptr is invalid argument");

		//Retrieve the size of the array from the header made at allocation time
		size_t length = *(((size_t*)array) - 1);

		//Call the destructor of T for each instance in the array
		for (size_t i = 0; i < length; i++)
			array[i].~T();

		//Calculate how much extra memory was allocated to store the length before the array
		uint8_t headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		//Call Deallocate on the allocator with the address at the begining of the array with the additional header memory included
		allocator->Deallocate(array - headerSize);
	}

	inline void* PointerMath::AlignForward(void* address, const uint8_t& alignment)
	{
		return (void*)((reinterpret_cast<uintptr_t>(address) + static_cast<uintptr_t>(alignment - 1)) & static_cast<uintptr_t>(~(alignment - 1)));
	}

	inline const void* PointerMath::AlignForward(const void* address, const uint8_t& alignment)
	{
		return (void*)((reinterpret_cast<uintptr_t>(address) + static_cast<uintptr_t>(alignment - 1)) & static_cast<uintptr_t>(~(alignment - 1)));
	}

	inline void* PointerMath::AlignBackward(void* address, const uint8_t& alignment)
	{
		return (void*)(reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(~(alignment - 1)));
	}

	inline const void* PointerMath::AlignBackward(const void* address, const uint8_t& alignment)
	{
		return (void*)(reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(~(alignment - 1)));
	}

	inline uint8_t PointerMath::AlignForwardAdjustment(const void* address, const uint8_t& alignment)
	{
		uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment - 1));

		if (adjustment == alignment)
			return 0; //already aligned

		return adjustment;
	}

	inline uint8_t PointerMath::AlignForwardAdjustmentWithHeader(const void* address, const uint8_t& alignment, const uint8_t& headerSize)
	{
		uint8_t adjustment = AlignForwardAdjustment(address, alignment);

		uint8_t neededSpace = headerSize;

		if (adjustment < neededSpace)
		{
			neededSpace -= adjustment;

			//Increase adjustment to fit header
			adjustment += alignment * (neededSpace / alignment);

			if (neededSpace % alignment > 0)
				adjustment += alignment;
		}

		return adjustment;
	}

	inline uint8_t PointerMath::AlignBackwardAdjustment(const void* address, const uint8_t& alignment)
	{
		uint8_t adjustment = reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment - 1);

		if (adjustment == alignment)
			return 0; //already aligned

		return adjustment;
	}

	inline void* PointerMath::Add(void* p, const size_t& x)
	{
		return (void*)(reinterpret_cast<uintptr_t>(p) + x);
	}

	inline const void* PointerMath::Add(const void* p, const size_t& x)
	{
		return (const void*)(reinterpret_cast<uintptr_t>(p) + x);
	}

	inline void* PointerMath::Subtract(void* p, const size_t& x)
	{
		return (void*)(reinterpret_cast<uintptr_t>(p) - x);
	}

	inline const void* PointerMath::Subtract(const void* p, const size_t& x)
	{
		return (const void*)(reinterpret_cast<uintptr_t>(p) - x);
	}
}
#endif //!ALLOCATOR_H
