#include <gtest/gtest.h>

#include "../include/Directives/BYT_DIR.h"
#include "../include/Directives/CSTR_DIR.h"
#include "../include/Directives/INT_DIR.h"
#include "../include/Directives/STR_DIR.h"

#include <stdexcept>
#include <cstdint>
#include <vector>

#include <iostream>
#include <sstream>

#include <Workpiece.h>

using namespace ASMFramework;

class ASMDirectivesTesting : public ::testing::Test
{
protected:
	Workpiece _workpiece;

	void SetUp() override
	{
		
	}

	void TearDown() override
	{
		
	}
};

TEST_F(ASMDirectivesTesting, Validate_BYT)
{
	BYT_DIR _byt;

	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"ARG1", "ARG2"}), std::runtime_error);
	
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"#-122"}), std::runtime_error);
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"#300"}), std::runtime_error);
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"#FFF"}), std::runtime_error);
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"#999999999999"}), std::runtime_error);

	ASSERT_NO_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"#122"}));

	EXPECT_EQ(_workpiece._dataSegmentBin.back(), 122);
	
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"-0x122"}), std::runtime_error);
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"0x300"}), std::runtime_error);
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"0xG"}), std::runtime_error);
	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"0xFFFFFFFFFF"}), std::runtime_error);
	
	ASSERT_NO_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"0xFF"}));

	EXPECT_EQ(_workpiece._dataSegmentBin.back(), 0xFF);

	ASSERT_NO_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"'n'"}));

	EXPECT_EQ(_workpiece._dataSegmentBin.back(), 'n');

	EXPECT_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"'\\g'"}), std::runtime_error);

	ASSERT_NO_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"'\\n'"}));

	EXPECT_EQ(_workpiece._dataSegmentBin.back(), '\n');

	ASSERT_NO_THROW(_byt.Implementation(&_workpiece, std::vector<std::string>{"'\\t'"}));

	EXPECT_EQ(_workpiece._dataSegmentBin.back(), '\t');
}

TEST_F(ASMDirectivesTesting, Validate_CSTR)
{
	CSTR_DIR _cstr;

	ASSERT_THROW(_cstr.Implementation(&_workpiece, std::vector<std::string>{}), ASMDirective::NotImplemented);
}

TEST_F(ASMDirectivesTesting, Validate_INT)
{
	INT_DIR _int;

	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"ARG1", "ARG2"}), std::runtime_error);

	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"#-2147483649"}), std::runtime_error);
	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"#2147483648"}), std::runtime_error);
	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"#FFF"}), std::runtime_error);
	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"#999999999999"}), std::runtime_error);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"#-2147483648"}));

	uint8_t* _bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], 0x00);
	EXPECT_EQ(_bytePtr[1], 0x00);
	EXPECT_EQ(_bytePtr[2], 0x00);
	EXPECT_EQ(_bytePtr[3], 0x80);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"#2147483647"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], 0xFF);
	EXPECT_EQ(_bytePtr[1], 0xFF);
	EXPECT_EQ(_bytePtr[2], 0xFF);
	EXPECT_EQ(_bytePtr[3], 0x7F);

	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"-0x80000001"}), std::runtime_error);
	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"0xG"}), std::runtime_error);
	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"0xFFFFFFFFFF"}), std::runtime_error);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"0x80000000"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], 0x00);
	EXPECT_EQ(_bytePtr[1], 0x00);
	EXPECT_EQ(_bytePtr[2], 0x00);
	EXPECT_EQ(_bytePtr[3], 0x80);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"-0x80000000"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], 0x00);
	EXPECT_EQ(_bytePtr[1], 0x00);
	EXPECT_EQ(_bytePtr[2], 0x00);
	EXPECT_EQ(_bytePtr[3], 0x80);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"0x7FFFFFFF"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], 0xFF);
	EXPECT_EQ(_bytePtr[1], 0xFF);
	EXPECT_EQ(_bytePtr[2], 0xFF);
	EXPECT_EQ(_bytePtr[3], 0x7F);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"'n'"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], 'n');
	EXPECT_EQ(_bytePtr[1], 0x00);
	EXPECT_EQ(_bytePtr[2], 0x00);
	EXPECT_EQ(_bytePtr[3], 0x00);

	EXPECT_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"'\\g'"}), std::runtime_error);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"'\\n'"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], '\n');
	EXPECT_EQ(_bytePtr[1], 0x00);
	EXPECT_EQ(_bytePtr[2], 0x00);
	EXPECT_EQ(_bytePtr[3], 0x00);

	ASSERT_NO_THROW(_int.Implementation(&_workpiece, std::vector<std::string>{"'\\t'"}));

	_bytePtr = _workpiece._dataSegmentBin.data() + _workpiece._dataSegmentBin.size() - 4;

	EXPECT_EQ(_bytePtr[0], '\t');
	EXPECT_EQ(_bytePtr[1], 0x00);
	EXPECT_EQ(_bytePtr[2], 0x00);
	EXPECT_EQ(_bytePtr[3], 0x00);
}

TEST_F(ASMDirectivesTesting, Validate_STR)
{
	STR_DIR _str;

	ASSERT_THROW(_str.Implementation(&_workpiece, std::vector<std::string>{}), ASMDirective::NotImplemented);
}