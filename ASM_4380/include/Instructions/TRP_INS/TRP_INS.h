#ifndef TRP_INS_H
#define TRP_INS_H

#include <ASMInstruction.h>



struct TRP_INS : public ASMFramework::ASMInstruction
{
public:
	TRP_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !TRP_INS_H
