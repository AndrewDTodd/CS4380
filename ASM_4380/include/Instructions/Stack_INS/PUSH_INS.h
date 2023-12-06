#ifndef PUSH_INS_H
#define PUSH_INS_H

#include <ASMInstruction.h>



struct PUSH_INS : public ASMFramework::ASMInstruction
{
public:
	PUSH_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !PUSH_INS_H
