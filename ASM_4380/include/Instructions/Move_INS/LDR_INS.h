#ifndef LDR_INS_H
#define LDR_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct LDR_INS : public ASMFramework::Instruction
{
public:
	LDR_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !LDR_INS_H
