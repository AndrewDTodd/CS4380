#ifndef PASS_TWO_H
#define PASS_TWO_H

#include <Pass.h>

using namespace ASMFramework;

class PassTwo : public Pass
{
public:
	void Execute(const Workpiece* const& workpiece, const std::unique_ptr<const std::ifstream>& fileStream, const LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_TWO_H
