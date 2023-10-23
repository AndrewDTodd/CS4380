#ifndef ADD_INS_H
#define ADD_INS_H

#include <ASMInstruction.h>

struct ADD_INS : public ASMFramework::ASMInstruction
{
public:
	ADD_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !ADD_INS_H
