#ifndef POP_INS_H
#define POP_INS_H

#include <ASMInstruction.h>



struct POP_INS : public ASMFramework::ASMInstruction
{
public:
	POP_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !POP_INS_H
