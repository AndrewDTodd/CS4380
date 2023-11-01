#ifndef MUL_INS_H
#define MUL_INS_H

#include <ASMInstruction.h>



struct MUL_INS : public ASMFramework::ASMInstruction
{
public:
	MUL_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !MUL_INS_H
