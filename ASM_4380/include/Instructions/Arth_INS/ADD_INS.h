#ifndef ADD_INS_H
#define ADD_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct ADD_INS : public ASMFramework::Instruction
{
public:
	ADD_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !ADD_INS_H
