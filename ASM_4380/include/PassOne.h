#ifndef PASS_ONE_H
#define PASS_ONE_H

#include <Pass.h>

using namespace ASMFramework;

class PassOne : public Pass
{
public:
	void Execute(const Workpiece* const& workpiece, const std::unique_ptr<const std::ifstream>& fileStream, const LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_ONE_H
