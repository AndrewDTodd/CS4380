#ifndef PASS_TWO_ASSEMBLE_H
#define PASS_TWO_ASSEMBLE_H

#include <Pass.h>
#include <LanguageDefinition.h>
#include <Workpiece.h>

#include <filesystem>
#include <memory>
#include <vector>
#include <string>

class PassTwo_Assemble : public ASMFramework::Pass
{
private:
	mutable bool _fail = false;

	void ProcessDataSegment(size_t& byteNum, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const;

	void ProcessCodeSegment(size_t& byteNum, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const;

	void ProcessUnresolvedLabels(ASMFramework::Workpiece* const& workpiece) const;

public:
	void Execute(ASMFramework::Workpiece* const& workpiece, const std::filesystem::path& filePath, const ASMFramework::LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_TWO_ASSEMBLE_H
