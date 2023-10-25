#ifndef PASS_ONE_TOKENIZATION_H
#define PASS_ONE_TOKENIZATION_H

#include <Pass.h>
#include <LanguageDefinition.h>
#include <Workpiece.h>

#include <filesystem>
#include <memory>
#include <vector>
#include <string>

#include <gtest/gtest_prod.h>

class PassOne_Tokenization : public ASMFramework::Pass
{
private:
	FRIEND_TEST(PassOneTesting, Validate_TokenizeLine);
	std::pair<std::vector<std::string>, std::string> TokenizeLine(const std::string& line) const;

	FRIEND_TEST(PassOneTesting, Validate_AddLabel);
	void AddLabel(const std::string& label, ASMFramework::Workpiece* const& workpiece) const;

	//FRIEND_TEST(PassOneTesting, Validate_ProcessDataSegment);
	void ProcessDataSegment(size_t& lineNum, ASMFramework::Workpiece* const& workpiece, std::ifstream& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const;

	FRIEND_TEST(PassOneTesting, Validate_HandleDirection);
	void HandleDirective(const size_t& lineNum, std::string&& label, const std::string& directive, const std::vector<std::string>& arguments, std::string&& comment, 
		ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const;

	//FRIEND_TEST(PassOneTesting, Validate_ProcessCodeSegment);
	void ProcessCodeSegment(size_t& lineNum, ASMFramework::Workpiece* const& workpiece, std::ifstream& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const;

	FRIEND_TEST(PassOneTesting, Validate_HandleInstruction);
	void HandleInstruction(const size_t& lineNum, const std::string& instruction, const std::vector<std::string>& arguments, std::string&& comment, 
		std::vector<ASMFramework::CodeSegmentItem>* const& segment, const ASMFramework::LanguageDefinition* const& langDef) const;

	FRIEND_TEST(PassOneTesting, Validate_HandleCodeSegmentItem);
	void HandleCodeSegmentItem(const std::string& label, const std::vector<ASMFramework::CodeSegmentItem>& segment,
		ASMFramework::Workpiece* const& workpiece) const;

public:
	void Execute(ASMFramework::Workpiece* const& workpiece, const std::filesystem::path& filePath, const ASMFramework::LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_ONE_TOKENIZATION_H
