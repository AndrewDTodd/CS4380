#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>
#include <filesystem>

#include "../include/PassTwo_Assemble.h"
#include "../include/LanguageDefinition_4380.h"
#include <Workpiece.h>

class PassTwoTesting : public ::testing::Test
{
protected:
	ASMFramework::Workpiece _workpiece;
	LanguageDefinition_4380 _langDef;
	std::ostringstream coutBuffer;
	std::streambuf* oldCoutBuf;
	std::stringstream buffer;
	std::streambuf* old;

	std::filesystem::path filePath = std::filesystem::path("fake/path");

	PassTwo_Assemble _pass;

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

TEST_F(PassTwoTesting, Validate_Execute)
{
	_pass._fail = true;
	EXPECT_THROW(_pass.Execute(&_workpiece, filePath, &_langDef), std::runtime_error);
}