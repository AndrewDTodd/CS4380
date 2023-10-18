#ifndef ADI_INS_H
#define ADI_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct ADI_INS : public ASMFramework::Instruction
{
public:
	ADI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !ADI_INS_H
