#ifndef DIVI_INS_H
#define DIVI_INS_H

#include <ASMInstruction.h>



struct DIVI_INS : public ASMFramework::ASMInstruction
{
public:
	DIVI_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !DIVI_INS_H
