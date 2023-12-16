#include <gtest/gtest.h>

#include "../include/Instructions/ASM_Instructions.h"

#include <stdexcept>
#include <cstdint>
#include <vector>

#include <iostream>
#include <sstream>

#include <Workpiece.h>
#include "../include/LanguageDefinition_4380.h"

using namespace ASMFramework;

class ASMInstructionsTesting : public ::testing::Test
{
protected:
	Workpiece _workpiece;
	LanguageDefinition_4380 _langDef;
	std::vector<uint8_t> _buffer;

	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

//ARTH_INS ***********************************************************************
TEST_F(ASMInstructionsTesting, Validate_ADD)
{
	ADD_INS _add;

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", "R0"}), std::out_of_range);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "R0"}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "R0"}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "R0"}), std::runtime_error);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "R0"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "R1"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 13);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 1);
}

TEST_F(ASMInstructionsTesting, Validate_ADI)
{
	ADI_INS _add;

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", ""}), std::out_of_range);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", ""}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", ""}), std::runtime_error);
	
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#FFF"}), std::runtime_error);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "#12"}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "#12"}), std::runtime_error);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "#12"}), std::runtime_error);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "#12"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "#12"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "#12"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#12345"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 12345);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#-12345"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -12345);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "-0x80000001"}), std::runtime_error);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "-0x80000000"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -2147483648);

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0xFFFFFFFFFF"}), std::runtime_error);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0x80000000"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -2147483648);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0x7FFFFFFF"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 2147483647);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'n'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 'n');

	EXPECT_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\g'"}), std::runtime_error);

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\n'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], '\n');

	ASSERT_NO_THROW(_add.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\t'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 14);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], '\t');
}

TEST_F(ASMInstructionsTesting, Validate_DIVI)
{
	DIVI_INS _divi;

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", ""}), std::out_of_range);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", ""}), std::runtime_error);
	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", ""}), std::runtime_error);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#FFF"}), std::runtime_error);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "#12"}), std::runtime_error);
	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "#12"}), std::runtime_error);
	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "#12"}), std::runtime_error);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "#12"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "#12"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "#12"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#12345"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 12345);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#-12345"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -12345);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "-0x80000001"}), std::runtime_error);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "-0x80000000"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -2147483648);

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0xFFFFFFFFFF"}), std::runtime_error);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0x80000000"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -2147483648);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0x7FFFFFFF"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 2147483647);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'n'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 'n');

	EXPECT_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\g'"}), std::runtime_error);

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\n'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], '\n');

	ASSERT_NO_THROW(_divi.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\t'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 34);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], '\t');
}

TEST_F(ASMInstructionsTesting, Validate_DIV)
{
	DIV_INS _div;

	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", "R0"}), std::out_of_range);

	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "R0"}), std::runtime_error);
	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "R0"}), std::runtime_error);
	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "R0"}), std::runtime_error);

	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "R0"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_div.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "R1"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 17);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 1);
}

TEST_F(ASMInstructionsTesting, Validate_MULI)
{
	MULI_INS _muli;

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", ""}), std::out_of_range);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", ""}), std::runtime_error);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#FFF"}), std::runtime_error);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "#12"}), std::runtime_error);
	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "#12"}), std::runtime_error);
	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "#12"}), std::runtime_error);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "#12"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "#12"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "#12"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#12345"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 12345);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "#-12345"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -12345);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "-0x80000001"}), std::runtime_error);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "-0x80000000"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -2147483648);

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0xFFFFFFFFFF"}), std::runtime_error);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0x80000000"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], -2147483648);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "0x7FFFFFFF"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 2147483647);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'n'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 'n');

	EXPECT_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\g'"}), std::runtime_error);

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\n'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], '\n');

	ASSERT_NO_THROW(_muli.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "'\\t'"}));

	_intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 33);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], '\t');
}

TEST_F(ASMInstructionsTesting, Validate_MUL)
{
	MUL_INS _mul;

	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", "R0"}), std::out_of_range);

	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "R0"}), std::runtime_error);
	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "R0"}), std::runtime_error);
	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "R0"}), std::runtime_error);

	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "R0"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_mul.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "R1"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 16);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 1);
}

TEST_F(ASMInstructionsTesting, Validate_SUB)
{
	SUB_INS _sub;

	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG"}), std::runtime_error);
	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"ARG1", "ARG2", "ARG3"}), std::runtime_error);

	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R-12", "R0"}), std::out_of_range);

	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"PC", "R0"}), std::runtime_error);
	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SL", "R0"}), std::runtime_error);
	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SB", "R0"}), std::runtime_error);

	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"SP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"FP", "R0"}), ASMFramework::ASMInstruction::Warning);
	EXPECT_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"HP", "R0"}), ASMFramework::ASMInstruction::Warning);

	ASSERT_NO_THROW(_sub.Implementation(_buffer, &_workpiece, &_langDef, std::vector<std::string>{"R0", "R1"}));

	int32_t* _intPtr = reinterpret_cast<int32_t*>(_buffer.data() + _buffer.size() - sizeof(int32_t) * 3);

	EXPECT_EQ(_intPtr[0], 15);
	EXPECT_EQ(_intPtr[1], 0);
	EXPECT_EQ(_intPtr[2], 1);
}
//********************************************************************************

//Comp_INS ***********************************************************************

//********************************************************************************