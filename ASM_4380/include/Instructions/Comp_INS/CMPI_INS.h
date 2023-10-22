#ifndef CMPI_INS_H
#define CMPI_INS_H

#include <ASMInstruction.h>



struct CMPI_INS : public ASMFramework::ASMInstruction
{
public:
	CMPI_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !CMPI_INS_H
