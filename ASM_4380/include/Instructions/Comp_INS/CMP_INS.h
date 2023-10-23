#ifndef CMP_INS_H
#define CMP_INS_H

#include <ASMInstruction.h>



struct CMP_INS : public ASMFramework::ASMInstruction
{
public:
	CMP_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !CMP_INS_H
