#ifndef LCK_INS_H
#define LCK_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct LCK_INS : public ASMFramework::Instruction
{
public:
	LCK_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !LCK_INS_H
