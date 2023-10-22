#ifndef DIVI_INS_H
#define DIVI_INS_H

#include <ASMInstruction.h>



struct DIVI_INS : public ASMFramework::ASMInstruction
{
public:
	DIVI_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !DIVI_INS_H
