#ifndef MOV_INS_H
#define MOV_INS_H

#include <ASMInstruction.h>



struct MOV_INS : public ASMFramework::ASMInstruction
{
public:
	MOV_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !MOV_INS_H
