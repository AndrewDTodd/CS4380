#ifndef JMP_INS_H
#define JMP_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct JMP_INS : public ASMFramework::ASMInstruction
{
public:
	JMP_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !JMP_INS_H
