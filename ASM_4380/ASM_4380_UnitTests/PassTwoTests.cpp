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

TEST_F(PassTwoTesting, Validate_ProcessUnresolvedLabels)
{
	size_t byteCount = 104;

	_workpiece._dataSegmentBin.resize(100);

	_workpiece._symbolTable["LabelOne"] = byteCount;

	_workpiece._codeSegmentBins.emplace_back("LabelOne", std::vector<uint8_t>());
	std::vector<uint8_t>& _bufferOne = _workpiece._codeSegmentBins.back().second;

	_bufferOne.resize(_bufferOne.size() + 20);

	size_t buffOffset = _bufferOne.size() - sizeof(int32_t);

	size_t deferredOne = buffOffset;

	_workpiece._unresolvedLabels["LabelTwo"].push_back({ &_bufferOne, buffOffset });

	_bufferOne.resize(_bufferOne.size() + 10);

	buffOffset = _bufferOne.size() - sizeof(int32_t);

	size_t deferredTwo = buffOffset;

	_workpiece._unresolvedLabels["LabelThree"].push_back({ &_bufferOne, buffOffset });

	_bufferOne.resize(_bufferOne.size() + 4);

	byteCount += _bufferOne.size();

	_workpiece._symbolTable["LabelTwo"] = byteCount;

	_workpiece._codeSegmentBins.emplace_back("LabelTwo", std::vector<uint8_t>());

	std::vector<uint8_t>& _bufferTwo = _workpiece._codeSegmentBins.back().second;

	_bufferTwo.resize(_bufferTwo.size() + 15);

	buffOffset = _bufferTwo.size() - sizeof(int32_t);

	size_t deferredThree = buffOffset;

	_workpiece._unresolvedLabels["LabelThree"].push_back({ &_bufferTwo, buffOffset });

	_bufferTwo.resize(_bufferTwo.size() + 20);

	byteCount += _bufferTwo.size();

	_workpiece._symbolTable["LabelThree"] = byteCount;

	_workpiece._codeSegmentBins.emplace_back("LabelThree", std::vector<uint8_t>());

	std::vector<uint8_t>& _bufferThree = _workpiece._codeSegmentBins.back().second;

	_bufferThree.resize(_bufferThree.size() + 8);

	buffOffset = _bufferThree.size() - sizeof(int32_t);

	size_t deferredFour = buffOffset;

	_workpiece._unresolvedLabels["LabelOne"].push_back({ &_bufferThree, buffOffset });

	_bufferThree.resize(_bufferThree.size() + 12);

	byteCount += _bufferThree.size();

	_pass.ProcessUnresolvedLabels(&_workpiece);

	EXPECT_EQ(*reinterpret_cast<int32_t*>(_bufferOne.data() + deferredOne), _workpiece._symbolTable["LabelTwo"]);
	EXPECT_EQ(*reinterpret_cast<int32_t*>(_bufferOne.data() + deferredTwo), _workpiece._symbolTable["LabelThree"]);

	EXPECT_EQ(*reinterpret_cast<int32_t*>(_bufferTwo.data() + deferredThree), _workpiece._symbolTable["LabelThree"]);

	EXPECT_EQ(*reinterpret_cast<int32_t*>(_bufferThree.data() + deferredFour), _workpiece._symbolTable["LabelOne"]);
}