#ifndef PASS_ONE_H
#define PASS_ONE_H

#include <Pass.h>
#include <LanguageDefinition.h>
#include <Workpiece.h>

#include <fstream>
#include <memory>
#include <vector>
#include <string>

class PassOne_Tokenization : public ASMFramework::Pass
{
private:
	std::pair<std::vector<std::string>, std::string> TokenizeLine(const std::string& line) const;

	void AddLabel(const std::string& label, ASMFramework::Workpiece* const& workpiece) const;

	void ProcessDataSegment(size_t& lineNum, ASMFramework::Workpiece* const& workpiece, const std::unique_ptr<std::ifstream>& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const;

	void HandleDirective(std::string&& label, const std::string& directive, const std::vector<std::string>& arguments, std::string&& comment, 
		ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const;

	void ProcessCodeSegment(size_t& lineNum, ASMFramework::Workpiece* const& workpiece, const std::unique_ptr<std::ifstream>& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const;

	void HandleInstruction(const std::string& instruction, const std::vector<std::string>& arguments, std::string&& comment, 
		std::vector<ASMFramework::CodeSegmentItem>* const& segment, const ASMFramework::LanguageDefinition* const& langDef) const;

	void HandleCodeSegmentItem(const std::string& label, const std::vector<ASMFramework::CodeSegmentItem>& segment,
		ASMFramework::Workpiece* const& workpiece) const;

public:
	void Execute(ASMFramework::Workpiece* const& workpiece, const std::unique_ptr<std::ifstream>& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_ONE_H
