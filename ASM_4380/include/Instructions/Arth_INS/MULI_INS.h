#ifndef MULI_INS_H
#define MULI_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct MULI_INS : public ASMFramework::ASMInstruction
{
public:
	MULI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !MULI_INS_H
