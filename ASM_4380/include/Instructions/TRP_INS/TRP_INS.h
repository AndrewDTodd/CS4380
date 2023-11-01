#ifndef TRP_INS_H
#define TRP_INS_H

#include <ASMInstruction.h>



struct TRP_INS : public ASMFramework::ASMInstruction
{
public:
	TRP_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !TRP_INS_H
