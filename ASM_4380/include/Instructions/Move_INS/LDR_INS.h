#ifndef LDR_INS_H
#define LDR_INS_H

#include <ASMInstruction.h>



struct LDR_INS : public ASMFramework::ASMInstruction
{
public:
	LDR_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !LDR_INS_H
