#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>
#include <memory>
#include <sstream>
#include <iostream>

#include "../include/ASM4380.h"

class AssemblerTesting : public ::testing::Test
{
protected:
	std::shared_ptr<ASM4380> _instance;
	std::ostringstream coutBuffer;
	std::streambuf* oldCoutBuf;

	void SetUp() override
	{
		oldCoutBuf = std::cout.rdbuf(coutBuffer.rdbuf());

		_instance = ASM4380::GetInstance();
	}

	void TearDown() override
	{
		_instance->ShutDown();

		std::cout.rdbuf(oldCoutBuf);
	}
};

TEST_F(AssemblerTesting, Validate_ProcessASM)
{
	EXPECT_THROW(_instance->ProcessASM("fake_directory/fakeFile"), std::invalid_argument);

	std::stringstream buffer;
	std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

	EXPECT_THROW(_instance->ProcessASM(TEST_TXT_PATH), std::runtime_error);

	std::string output = buffer.str();
	std::cerr.rdbuf(old);

	EXPECT_EQ(output, "**Warning** >> The extension for the provided file is \".txt\", expected .asm. Is this a valid assembly file? Use the .asm extension.\n");
}