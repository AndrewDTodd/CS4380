#ifndef BRZ_INS_H
#define BRZ_INS_H

#include <ASMInstruction.h>



struct BRZ_INS : public ASMFramework::ASMInstruction
{
public:
	BRZ_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // BRZ_INS_H
