#ifndef BLT_INS_H
#define BLT_INS_H

#include <ASMInstruction.h>



struct BLT_INS : public ASMFramework::ASMInstruction
{
public:
	BLT_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !JMP_INS_H
