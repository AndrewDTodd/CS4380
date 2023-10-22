#ifndef ADI_INS_H
#define ADI_INS_H

#include <ASMInstruction.h>



struct ADI_INS : public ASMFramework::ASMInstruction
{
public:
	ADI_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !ADI_INS_H
