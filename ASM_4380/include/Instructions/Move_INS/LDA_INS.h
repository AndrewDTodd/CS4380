#ifndef LDA_INS_H
#define LDA_INS_H

#include <ASMInstruction.h>



struct LDA_INS : public ASMFramework::ASMInstruction
{
public:
	LDA_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !LDA_INS_H
