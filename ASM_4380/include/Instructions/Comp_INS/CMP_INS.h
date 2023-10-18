#ifndef CMP_INS_H
#define CMP_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct CMP_INS : public ASMFramework::Instruction
{
public:
	CMP_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !CMP_INS_H
