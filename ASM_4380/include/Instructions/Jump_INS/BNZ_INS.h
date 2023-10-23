#ifndef BNZ_INS_H
#define BNZ_INS_H

#include <ASMInstruction.h>



struct BNZ_INS : public ASMFramework::ASMInstruction
{
public:
	BNZ_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !BNZ_INS_H
