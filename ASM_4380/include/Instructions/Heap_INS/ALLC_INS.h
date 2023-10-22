#ifndef ALLC_INS_H
#define ALLC_INS_H

#include <ASMInstruction.h>



struct ALLC_INS : public ASMFramework::ASMInstruction
{
public:
	ALLC_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !ALLC_INS_H
