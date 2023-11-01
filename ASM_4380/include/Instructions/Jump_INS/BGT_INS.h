#ifndef BGT_INS_H
#define BGT_INS_H

#include <ASMInstruction.h>



struct BGT_INS : public ASMFramework::ASMInstruction
{
public:
	BGT_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !JMP_INS_H
