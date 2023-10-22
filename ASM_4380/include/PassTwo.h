#ifndef PASS_TWO_H
#define PASS_TWO_H

#include <Pass.h>

class PassTwo : public ASMFramework::Pass
{
public:
	void Execute(ASMFramework::Workpiece* const& workpiece, const std::unique_ptr<std::ifstream>& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_TWO_H
