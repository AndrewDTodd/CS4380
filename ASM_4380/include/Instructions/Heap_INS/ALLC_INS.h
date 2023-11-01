#ifndef ALLC_INS_H
#define ALLC_INS_H

#include <ASMInstruction.h>



struct ALLC_INS : public ASMFramework::ASMInstruction
{
public:
	ALLC_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !ALLC_INS_H
