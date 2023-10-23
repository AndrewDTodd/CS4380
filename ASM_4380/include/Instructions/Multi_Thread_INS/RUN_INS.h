#ifndef RUN_INS_H
#define RUN_INS_H

#include <ASMInstruction.h>



struct RUN_INS : public ASMFramework::ASMInstruction
{
public:
	RUN_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !RUN_INS_H
