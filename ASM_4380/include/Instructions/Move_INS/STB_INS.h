#ifndef STB_INS_H
#define STB_INS_H

#include <ASMInstruction.h>



struct STB_INS : public ASMFramework::ASMInstruction
{
public:
	STB_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !STB_INS_H
