#ifndef PASS_THREE_H
#define PASS_THREE_H

#include <Pass.h>

using namespace ASMFramework;

class PassThree : public Pass
{
public:
	void Execute(const Workpiece* const& workpiece, const std::unique_ptr<const std::ifstream>& fileStream, const LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_THREE_H
