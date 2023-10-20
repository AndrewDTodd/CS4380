#ifndef NOT_INS_H
#define NOT_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct NOT_INS : public ASMFramework::ASMInstruction
{
public:
	NOT_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !NOT_INS_H
