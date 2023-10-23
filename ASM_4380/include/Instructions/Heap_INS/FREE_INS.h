#ifndef FREE_INS_H
#define FREE_INS_H

#include <ASMInstruction.h>



struct FREE_INS : public ASMFramework::ASMInstruction
{
public:
	FREE_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !FREE_INS_H
