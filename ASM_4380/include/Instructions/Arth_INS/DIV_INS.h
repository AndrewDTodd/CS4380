#ifndef DIV_INS_H
#define DIV_INS_H

#include <ASMInstruction.h>



struct DIV_INS : public ASMFramework::ASMInstruction
{
public:
	DIV_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !DIV_INS_H
