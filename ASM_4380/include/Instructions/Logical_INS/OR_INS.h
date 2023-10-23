#ifndef OR_INS_H
#define OR_INS_H

#include <ASMInstruction.h>



struct OR_INS : public ASMFramework::ASMInstruction
{
public:
	OR_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !OR_INS_H
