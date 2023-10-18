#ifndef OR_INS_H
#define OR_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct OR_INS : public ASMFramework::Instruction
{
public:
	OR_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !OR_INS_H
