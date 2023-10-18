#ifndef JMP_INS_H
#define JMP_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct JMP_INS : public ASMFramework::Instruction
{
public:
	JMP_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !JMP_INS_H
