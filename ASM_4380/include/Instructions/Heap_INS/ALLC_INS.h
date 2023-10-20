#ifndef ALLC_INS_H
#define ALLC_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct ALLC_INS : public ASMFramework::ASMInstruction
{
public:
	ALLC_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !ALLC_INS_H
