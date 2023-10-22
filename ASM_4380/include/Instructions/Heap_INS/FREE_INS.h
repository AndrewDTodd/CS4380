#ifndef FREE_INS_H
#define FREE_INS_H

#include <ASMInstruction.h>



struct FREE_INS : public ASMFramework::ASMInstruction
{
public:
	FREE_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !FREE_INS_H
