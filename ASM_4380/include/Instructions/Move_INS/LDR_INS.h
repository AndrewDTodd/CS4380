#ifndef LDR_INS_H
#define LDR_INS_H

#include <ASMInstruction.h>



struct LDR_INS : public ASMFramework::ASMInstruction
{
public:
	LDR_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !LDR_INS_H
