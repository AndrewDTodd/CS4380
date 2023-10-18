#ifndef LDA_INS_H
#define LDA_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct LDA_INS : public ASMFramework::Instruction
{
public:
	LDA_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !LDA_INS_H
