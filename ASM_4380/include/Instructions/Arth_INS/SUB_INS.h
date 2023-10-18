#ifndef SUB_INS_H
#define SUB_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct SUB_INS : public ASMFramework::Instruction
{
public:
	SUB_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !SUB_INS_H
