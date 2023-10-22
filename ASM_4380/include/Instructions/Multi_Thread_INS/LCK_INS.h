#ifndef LCK_INS_H
#define LCK_INS_H

#include <ASMInstruction.h>



struct LCK_INS : public ASMFramework::ASMInstruction
{
public:
	LCK_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !LCK_INS_H
