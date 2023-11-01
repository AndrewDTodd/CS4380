#ifndef STR_INS_H
#define STR_INS_H

#include <ASMInstruction.h>



struct STR_INS : public ASMFramework::ASMInstruction
{
public:
	STR_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !STR_INS_H
