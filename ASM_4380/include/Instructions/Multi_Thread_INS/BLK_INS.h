#ifndef BLK_INS_H
#define BLK_INS_H

#include <ASMInstruction.h>



struct BLK_INS : public ASMFramework::ASMInstruction
{
public:
	BLK_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !BLK_INS_H
