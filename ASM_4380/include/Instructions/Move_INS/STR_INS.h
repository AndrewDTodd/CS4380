#ifndef STR_INS_H
#define STR_INS_H

#include <ASMInstruction.h>



struct STR_INS : public ASMFramework::ASMInstruction
{
public:
	STR_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !STR_INS_H
