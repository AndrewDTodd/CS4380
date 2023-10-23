#ifndef ADI_INS_H
#define ADI_INS_H

#include <ASMInstruction.h>



struct ADI_INS : public ASMFramework::ASMInstruction
{
public:
	ADI_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !ADI_INS_H
