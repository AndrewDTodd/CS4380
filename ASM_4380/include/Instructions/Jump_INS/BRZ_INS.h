#ifndef BRZ_INS_H
#define BRZ_INS_H

#include <ASMInstruction.h>



struct BRZ_INS : public ASMFramework::ASMInstruction
{
public:
	BRZ_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // BRZ_INS_H
