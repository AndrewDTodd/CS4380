#ifndef POINTER_MATH_H
#define POINTER_MATH_H

#include <cstdint>
#include <cstddef>

namespace VMFramework
{
	class PointerMath
	{
	public:
		static void*	   AlignForward(void* address, const uint8_t& alignment);
		static const void* AlignForward(const void* address, const uint8_t& alignment);

		static void*	   AlignBackward(void* address, const uint8_t& alignment);
		static const void* AlignBackward(const void* address, const uint8_t& alignment);

		static uint8_t     AlignForwardAdjustment(const void* address, const uint8_t& alignment);
		static uint8_t     AlignForwardAdjustmentWithHeader(const void* address, const uint8_t& alignment, const uint8_t& headerSize);

		static uint8_t     AlignBackwardAdjustment(const void* address, const uint8_t& alignment);

		static void*       Add(void* p, const size_t& x);
		static const void* Add(const void* p, const size_t& x);

		static void*       Subtract(void* p, const size_t& x);
		static const void* Subtract(const void* p, const size_t& x);

		//Class is static, do not attempt to make instance
		PointerMath() = delete;
		~PointerMath() = delete;
		PointerMath(const PointerMath&) = delete;
		PointerMath& operator=(const PointerMath&) = delete;
		PointerMath(PointerMath&&) = delete;
		PointerMath& operator=(PointerMath&&) = delete;
	};
}
#endif //!POINTER_MATH_H
