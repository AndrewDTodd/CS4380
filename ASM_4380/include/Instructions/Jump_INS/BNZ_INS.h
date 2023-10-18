#ifndef BNZ_INS_H
#define BNZ_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct BNZ_INS : public ASMFramework::Instruction
{
public:
	BNZ_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !BNZ_INS_H
