#ifndef MOVI_INS_H
#define MOVI_INS_H

#include <ASMInstruction.h>



struct MOVI_INS : public ASMFramework::ASMInstruction
{
public:
	MOVI_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !MOVI_INS_H
