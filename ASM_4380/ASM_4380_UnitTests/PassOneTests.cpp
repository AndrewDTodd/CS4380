#include <gtest/gtest.h>

#include <stdexcept>
#include <cstdint>
#include <memory>
#include <sstream>
#include <iostream>
#include <istream>

#include "../include/PassOne_Tokenization.h"
#include "../include/LanguageDefinition_4380.h"
#include <Workpiece.h>

class PassOneTesting : public ::testing::Test
{
protected:
	ASMFramework::Workpiece _workpiece;
	LanguageDefinition_4380 _langDef;
	std::ostringstream coutBuffer;
	std::streambuf* oldCoutBuf;
	std::stringstream buffer;
	std::streambuf* old;

	PassOne_Tokenization _pass;

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

TEST_F(PassOneTesting, Validate_TokenizeLine)
{
	std::string input = "MAIN LDB R5, R6 ;comment";

	auto result = _pass.TokenizeLine(input);

	EXPECT_EQ(result.first.size(), 4);

	EXPECT_EQ(result.first[0], "MAIN");
	EXPECT_EQ(result.first[1], "LDB");
	EXPECT_EQ(result.first[2], "R5");
	EXPECT_EQ(result.first[3], "R6");

	EXPECT_EQ(result.second, ";comment");

	input = "MAIN LDB R5, R6";

	result = _pass.TokenizeLine(input);

	EXPECT_EQ(result.first.size(), 4);

	EXPECT_EQ(result.first[0], "MAIN");
	EXPECT_EQ(result.first[1], "LDB");
	EXPECT_EQ(result.first[2], "R5");
	EXPECT_EQ(result.first[3], "R6");

	EXPECT_EQ(result.second, "");

	input = " MAIN LDB R5, R6";

	result = _pass.TokenizeLine(input);

	EXPECT_EQ(result.first.size(), 4);

	EXPECT_EQ(result.first[0], "MAIN");
	EXPECT_EQ(result.first[1], "LDB");
	EXPECT_EQ(result.first[2], "R5");
	EXPECT_EQ(result.first[3], "R6");

	EXPECT_EQ(result.second, "");

	input = "SPACE .BYT ' '";

	result = _pass.TokenizeLine(input);

	EXPECT_EQ(result.first.size(), 3);

	EXPECT_EQ(result.first[0], "SPACE");
	EXPECT_EQ(result.first[1], ".BYT");
	EXPECT_EQ(result.first[2], "' '");

	EXPECT_EQ(result.second, "");

	input = "SPACE .BYT #16";

	result = _pass.TokenizeLine(input);

	EXPECT_EQ(result.first.size(), 3);

	EXPECT_EQ(result.first[0], "SPACE");
	EXPECT_EQ(result.first[1], ".BYT");
	EXPECT_EQ(result.first[2], "#16");

	EXPECT_EQ(result.second, "");

	input = "SPACE .BYT ##16";

	EXPECT_THROW(_pass.TokenizeLine(input), std::runtime_error);

	input = "SPACE ..BYT #16";

	EXPECT_THROW(_pass.TokenizeLine(input), std::runtime_error);
}

TEST_F(PassOneTesting, Validate_AddLabel)
{
	_pass.AddLabel("MAIN", &_workpiece);

	EXPECT_TRUE(_workpiece._symbolTable.contains("MAIN"));
}