#ifndef CMPI_INS_H
#define CMPI_INS_H

#include <ASMInstruction.h>



struct CMPI_INS : public ASMFramework::ASMInstruction
{
public:
	CMPI_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !CMPI_INS_H
