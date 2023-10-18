#ifndef MOVI_INS_H
#define MOVI_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct MOVI_INS : public ASMFramework::Instruction
{
public:
	MOVI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !MOVI_INS_H
