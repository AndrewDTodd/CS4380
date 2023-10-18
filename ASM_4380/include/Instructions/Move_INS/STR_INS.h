#ifndef STR_INS_H
#define STR_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct STR_INS : public ASMFramework::Instruction
{
public:
	STR_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !STR_INS_H
