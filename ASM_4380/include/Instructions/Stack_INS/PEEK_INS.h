#ifndef PEEK_INS_H
#define PEEK_INS_H

#include <ASMInstruction.h>



struct PEEK_INS : public ASMFramework::ASMInstruction
{
public:
	PEEK_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const override;
};
#endif // !PEEK_INS_H
