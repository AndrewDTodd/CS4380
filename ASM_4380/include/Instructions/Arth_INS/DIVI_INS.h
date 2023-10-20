#ifndef DIVI_INS_H
#define DIVI_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct DIVI_INS : public ASMFramework::ASMInstruction
{
public:
	DIVI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !DIVI_INS_H
