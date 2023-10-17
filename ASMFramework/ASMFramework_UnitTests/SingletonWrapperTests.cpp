#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>
#include <memory>

#include "../include/SingletonWrapper.h"

class TESTSingleton : public ASMFramework::SingletonWrapper<TESTSingleton>
{

};

class SingletonWrapperTesting : public ::testing::Test
{
protected:
	std::shared_ptr<TESTSingleton> _instance;

	void SetUp() override
	{
		_instance = TESTSingleton::GetInstance();
	}

	void TearDown() override
	{
	}
};

TEST_F(SingletonWrapperTesting, Validate_GetInstance)
{
	ASSERT_EQ(_instance, TESTSingleton::GetInstance());
}