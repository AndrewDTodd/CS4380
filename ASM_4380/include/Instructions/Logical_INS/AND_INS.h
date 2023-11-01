#ifndef AND_INS_H
#define AND_INS_H

#include <ASMInstruction.h>



struct AND_INS : public ASMFramework::ASMInstruction
{
public:
	AND_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !AND_INS_H
