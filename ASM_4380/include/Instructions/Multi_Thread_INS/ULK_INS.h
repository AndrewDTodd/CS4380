#ifndef ULK_INS_H
#define ULK_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct ULK_INS : public ASMFramework::Instruction
{
public:
	ULK_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !ULK_INS_H
