#ifndef ULK_INS_H
#define ULK_INS_H

#include <ASMInstruction.h>



struct ULK_INS : public ASMFramework::ASMInstruction
{
public:
	ULK_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !ULK_INS_H
