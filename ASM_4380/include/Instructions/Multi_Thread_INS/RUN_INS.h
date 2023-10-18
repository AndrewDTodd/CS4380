#ifndef RUN_INS_H
#define RUN_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct RUN_INS : public ASMFramework::Instruction
{
public:
	RUN_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !RUN_INS_H
