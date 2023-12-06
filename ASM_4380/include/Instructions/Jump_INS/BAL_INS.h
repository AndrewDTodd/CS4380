#ifndef BAL_INS_H
#define BAL_INS_H

#include <ASMInstruction.h>



struct BAL_INS : public ASMFramework::ASMInstruction
{
public:
	BAL_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !BAL_INS_H