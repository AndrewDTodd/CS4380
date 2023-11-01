#ifndef SUB_INS_H
#define SUB_INS_H

#include <ASMInstruction.h>



struct SUB_INS : public ASMFramework::ASMInstruction
{
public:
	SUB_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !SUB_INS_H
