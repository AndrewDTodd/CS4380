#ifndef BLT_INS_H
#define BLT_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct BLT_INS : public ASMFramework::ASMInstruction
{
public:
	BLT_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !JMP_INS_H
