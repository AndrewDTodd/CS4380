#ifndef AND_INS_H
#define AND_INS_H

#include <ASMInstruction.h>



struct AND_INS : public ASMFramework::ASMInstruction
{
public:
	AND_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !AND_INS_H
