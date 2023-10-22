#ifndef JMP_INS_H
#define JMP_INS_H

#include <ASMInstruction.h>



struct JMP_INS : public ASMFramework::ASMInstruction
{
public:
	JMP_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !JMP_INS_H
