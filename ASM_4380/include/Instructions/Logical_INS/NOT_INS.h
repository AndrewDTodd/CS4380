#ifndef NOT_INS_H
#define NOT_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct NOT_INS : public ASMFramework::Instruction
{
public:
	NOT_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !NOT_INS_H
