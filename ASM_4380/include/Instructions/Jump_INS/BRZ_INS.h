#ifndef BRZ_INS_H
#define BRZ_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct BRZ_INS : public ASMFramework::Instruction
{
public:
	BRZ_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // BRZ_INS_H
