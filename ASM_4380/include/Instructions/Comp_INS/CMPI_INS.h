#ifndef CMPI_INS_H
#define CMPI_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct CMPI_INS : public ASMFramework::Instruction
{
public:
	CMPI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !CMPI_INS_H
