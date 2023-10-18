#ifndef FREE_INS_H
#define FREE_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct FREE_INS : public ASMFramework::Instruction
{
public:
	FREE_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !FREE_INS_H
