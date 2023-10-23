#ifndef MULI_INS_H
#define MULI_INS_H

#include <ASMInstruction.h>



struct MULI_INS : public ASMFramework::ASMInstruction
{
public:
	MULI_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !MULI_INS_H
