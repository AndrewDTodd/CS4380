#ifndef AND_INS_H
#define AND_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct AND_INS : public ASMFramework::Instruction
{
public:
	AND_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !AND_INS_H
