#ifndef END_INS_H
#define END_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct END_INS : public ASMFramework::Instruction
{
public:
	END_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !END_INS_H
