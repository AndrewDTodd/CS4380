#ifndef BLK_INS_H
#define BLK_INS_H

#include <ASMInstruction.h>



struct BLK_INS : public ASMFramework::ASMInstruction
{
public:
	BLK_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !BLK_INS_H
