#ifndef END_INS_H
#define END_INS_H

#include <ASMInstruction.h>



struct END_INS : public ASMFramework::ASMInstruction
{
public:
	END_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !END_INS_H
