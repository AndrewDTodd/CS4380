#include <gtest/gtest.h>

#include <cstdint>

#include "../include/Allocator.h"

using namespace VMFramework;

TEST(PointerMathTests, Validate_AlignForward)
{
    // Test with a non-null address
    void* address = reinterpret_cast<void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignForward(address, 1), address);
    EXPECT_EQ(PointerMath::AlignForward(address, 4), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignForward(address, 8), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignForward(address, 16), reinterpret_cast<void*>(0x12345680));
    EXPECT_EQ(PointerMath::AlignForward(address, 32), reinterpret_cast<void*>(0x12345680));
    EXPECT_EQ(PointerMath::AlignForward(address, 64), reinterpret_cast<void*>(0x12345680));
}

TEST(PointerMathTests, Validate_AlignForwardConst)
{
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignForward(address, 1), address);
    EXPECT_EQ(PointerMath::AlignForward(address, 4), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignForward(address, 8), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignForward(address, 16), reinterpret_cast<const void*>(0x12345680));
    EXPECT_EQ(PointerMath::AlignForward(address, 32), reinterpret_cast<const void*>(0x12345680));
    EXPECT_EQ(PointerMath::AlignForward(address, 64), reinterpret_cast<const void*>(0x12345680));
}

TEST(PointerMathTests, Validate_AlignBackward)
{
    // Test with a non-null address for non-const version
    void* address = reinterpret_cast<void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignBackward(address, 1), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignBackward(address, 4), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignBackward(address, 8), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignBackward(address, 16), reinterpret_cast<void*>(0x12345670));
    EXPECT_EQ(PointerMath::AlignBackward(address, 32), reinterpret_cast<void*>(0x12345660));
    EXPECT_EQ(PointerMath::AlignBackward(address, 64), reinterpret_cast<void*>(0x12345640));
}

TEST(PointerMathTests, Validate_AlignBackwardConst)
{
    // Test with a non-null address for const version
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignBackward(address, 1), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignBackward(address, 4), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignBackward(address, 8), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::AlignBackward(address, 16), reinterpret_cast<const void*>(0x12345670));
    EXPECT_EQ(PointerMath::AlignBackward(address, 32), reinterpret_cast<const void*>(0x12345660));
    EXPECT_EQ(PointerMath::AlignBackward(address, 64), reinterpret_cast<const void*>(0x12345640));
}

TEST(PointerMathTests, Validate_AlignForwardAdjustment)
{
    // Test cases with different alignments
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(nullptr, 1), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(nullptr, 4), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(nullptr, 8), 0);

    // Test with a non-null address
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(address, 1), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(address, 4), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(address, 8), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(address, 16), 8);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(address, 32), 8);
    EXPECT_EQ(PointerMath::AlignForwardAdjustment(address, 64), 8);
}

TEST(PointerMathTests, Validate_AlignForwardAdjustmentWithHeader)
{
    // Test cases with different alignments and header sizes
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(nullptr, 1, 0), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(nullptr, 4, 0), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(nullptr, 8, 0), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(nullptr, 8, 1), 8);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(nullptr, 16, 4), 16);

    // Test with a non-null address
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(address, 1, 0), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(address, 4, 0), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(address, 8, 0), 0);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(address, 16, 4), 8);
    EXPECT_EQ(PointerMath::AlignForwardAdjustmentWithHeader(address, 32, 8), 8);
}

TEST(PointerMathTests, Validate_AlignBackwardAdjustment)
{
    // Test cases with different alignments
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(nullptr, 1), 0);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(nullptr, 4), 0);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(nullptr, 8), 0);

    // Test with a non-null address
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(address, 1), 0);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(address, 4), 0);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(address, 8), 0);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(address, 16), 8);
    EXPECT_EQ(PointerMath::AlignBackwardAdjustment(address, 32), 24);
}

TEST(PointerMathTests, Validate_Add)
{
    // Test with a non-null pointer
    void* address = reinterpret_cast<void*>(0x12345678);
    EXPECT_EQ(PointerMath::Add(address, 0), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::Add(address, 4), reinterpret_cast<void*>(0x1234567C));
    EXPECT_EQ(PointerMath::Add(address, 100), reinterpret_cast<void*>(0x123456DC));
}

TEST(PointerMathTests, Validate_AddConst)
{
    // Test with a non-null pointer for const version
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::Add(address, 0), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::Add(address, 4), reinterpret_cast<const void*>(0x1234567C));
    EXPECT_EQ(PointerMath::Add(address, 100), reinterpret_cast<const void*>(0x123456DC));
}

TEST(PointerMathTests, Validate_Subtract)
{
    // Test with a non-null pointer
    void* address = reinterpret_cast<void*>(0x12345678);
    EXPECT_EQ(PointerMath::Subtract(address, 0), reinterpret_cast<void*>(0x12345678));
    EXPECT_EQ(PointerMath::Subtract(address, 4), reinterpret_cast<void*>(0x12345674));
    EXPECT_EQ(PointerMath::Subtract(address, 100), reinterpret_cast<void*>(0x12345614));
}

TEST(PointerMathTests, Validate_SubtractConst)
{
    // Test with a non-null pointer for const version
    const void* address = reinterpret_cast<const void*>(0x12345678);
    EXPECT_EQ(PointerMath::Subtract(address, 0), reinterpret_cast<const void*>(0x12345678));
    EXPECT_EQ(PointerMath::Subtract(address, 4), reinterpret_cast<const void*>(0x12345674));
    EXPECT_EQ(PointerMath::Subtract(address, 100), reinterpret_cast<const void*>(0x12345614));
}