#ifndef MOV_INS_H
#define MOV_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct MOV_INS : public ASMFramework::Instruction
{
public:
	MOV_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !MOV_INS_H
