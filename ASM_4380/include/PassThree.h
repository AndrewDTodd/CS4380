#ifndef PASS_THREE_H
#define PASS_THREE_H

#include <Pass.h>

class PassThree : public ASMFramework::Pass
{
public:
	void Execute(ASMFramework::Workpiece* const& workpiece, const std::unique_ptr<std::ifstream>& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_THREE_H
