#ifndef LCK_INS_H
#define LCK_INS_H

#include <ASMInstruction.h>



struct LCK_INS : public ASMFramework::ASMInstruction
{
public:
	LCK_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !LCK_INS_H
