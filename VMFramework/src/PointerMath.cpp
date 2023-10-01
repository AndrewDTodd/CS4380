#include "../include/PointerMath.h"

#include <cstdint>
#include <cstddef>

namespace VMFramework
{
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