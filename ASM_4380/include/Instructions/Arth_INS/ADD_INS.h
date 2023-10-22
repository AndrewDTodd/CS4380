#ifndef ADD_INS_H
#define ADD_INS_H

#include <ASMInstruction.h>

struct ADD_INS : public ASMFramework::ASMInstruction
{
public:
	ADD_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !ADD_INS_H
