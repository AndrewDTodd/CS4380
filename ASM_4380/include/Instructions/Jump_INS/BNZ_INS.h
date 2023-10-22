#ifndef BNZ_INS_H
#define BNZ_INS_H

#include <ASMInstruction.h>



struct BNZ_INS : public ASMFramework::ASMInstruction
{
public:
	BNZ_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !BNZ_INS_H
