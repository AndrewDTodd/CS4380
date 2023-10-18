#ifndef ALCI_INS_H
#define ALCI_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct ALCI_INS : public ASMFramework::Instruction
{
public:
	ALCI_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !ALCI_INS_H
