#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>

#include "../include/ISA_4380.h"

#include "../include/Instructions/Instructions.h"

using namespace VMFramework;

class ISA_4380Testing : public ::testing::Test
{
protected:
	ISA_4380 _instance;

	void SetUp() override
	{
		
	}

	void TearDown() override
	{
		
	}
};

struct PassIns : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	PassIns(): Instruction(0)
	{

	}

	void Op(Process_4380* process) override
	{

	}
};

VMFramework::Instruction<int32_t, int32_t, Process_4380>* _passInstructions[] = { new PassIns() };

class PassISA : public VMFramework::ISA<int32_t, int32_t, Process_4380>
{
public:
	PassISA() : ISA<int32_t, int32_t, Process_4380>(_passInstructions, 1)
	{

	}
};

struct FailIns : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	FailIns() : Instruction(-1)
	{

	}

	void Op(Process_4380* process) override
	{

	}
};

VMFramework::Instruction<int32_t, int32_t, Process_4380>* _failInstructions[] = { new FailIns() };

class FailISA : public VMFramework::ISA<int32_t, int32_t, Process_4380>
{
public:
	FailISA() : ISA<int32_t, int32_t, Process_4380>(_failInstructions, 1)
	{

	}
};

TEST_F(ISA_4380Testing, Validate_Constructor)
{
	//Verify the ISA_4380 constructor imlementation doesnt cause exeption
	ASSERT_NO_THROW(ISA_4380 _instance);
}

TEST_F(ISA_4380Testing, Validate_InstructionSetAtBounds)
{
	//Verify that index 0 is nullptr
	EXPECT_EQ(_instance[0], nullptr);

	//Verify that index 1 (AND) is not null but AND
	EXPECT_EQ(typeid(*_instance[1]), typeid(JMP_L));

	//Verify that index 21 is not null but TRP
	EXPECT_EQ(typeid(*_instance[21]), typeid(TRP));
}

TEST(ISATesting, Validate_ConstructorValidInput)
{
	ASSERT_NO_THROW({ PassISA _instance; });
}

TEST(ISATesting, Validate_ConstructorBadInput)
{
	ASSERT_THROW({ FailISA _instance; }, std::out_of_range);
}

TEST(ISATesting, Validate_IndexOperatorGoodInput)
{
	PassISA* _instance;

	ASSERT_NO_THROW({ _instance = new PassISA(); });

	ASSERT_EQ(typeid(*_instance->operator[](0)), typeid(PassIns));
}

TEST(ISATesting, Validate_IndexOperatorBadInput)
{
	PassISA* _instance;

	ASSERT_NO_THROW({ _instance = new PassISA(); });

	ASSERT_THROW(_instance->operator[](-1), std::out_of_range);
}