#ifndef FREE_INS_H
#define FREE_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct FREE_INS : public ASMFramework::ASMInstruction
{
public:
	FREE_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !FREE_INS_H
