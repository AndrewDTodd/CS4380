#ifndef MUL_INS_H
#define MUL_INS_H

#include <ASMInstruction.h>



struct MUL_INS : public ASMFramework::ASMInstruction
{
public:
	MUL_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !MUL_INS_H
