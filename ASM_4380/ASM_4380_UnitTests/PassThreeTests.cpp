#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>
#include <filesystem>

#include "../include/PassThree_Serialize.h"
#include "../include/LanguageDefinition_4380.h"
#include <Workpiece.h>

class PassThreeTesting : public ::testing::Test
{
protected:
	ASMFramework::Workpiece _workpiece;
	LanguageDefinition_4380 _langDef;
	std::ostringstream coutBuffer;
	std::streambuf* oldCoutBuf;
	std::stringstream buffer;
	std::streambuf* old;

	std::filesystem::path filePath = std::filesystem::path("fake/path");

	PassThree_Serialize _pass;

	void SetUp() override
	{
		oldCoutBuf = std::cout.rdbuf(coutBuffer.rdbuf());
		old = std::cerr.rdbuf(buffer.rdbuf());
	}

	void TearDown() override
	{
		std::cout.rdbuf(oldCoutBuf);
		std::cerr.rdbuf(old);
	}
};

TEST_F(PassThreeTesting, Validate_Execute)
{
	EXPECT_THROW(_pass.Execute(&_workpiece, filePath, &_langDef), std::runtime_error);
}