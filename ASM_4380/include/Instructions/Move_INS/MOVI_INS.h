#ifndef MOVI_INS_H
#define MOVI_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct MOVI_INS : public ASMFramework::ASMInstruction
{
public:
	MOVI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !MOVI_INS_H
