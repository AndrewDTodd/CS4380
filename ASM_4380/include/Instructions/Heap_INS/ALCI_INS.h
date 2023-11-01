#ifndef ALCI_INS_H
#define ALCI_INS_H

#include <ASMInstruction.h>



struct ALCI_INS : public ASMFramework::ASMInstruction
{
public:
	ALCI_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !ALCI_INS_H
