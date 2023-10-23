#ifndef NOT_INS_H
#define NOT_INS_H

#include <ASMInstruction.h>



struct NOT_INS : public ASMFramework::ASMInstruction
{
public:
	NOT_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !NOT_INS_H
