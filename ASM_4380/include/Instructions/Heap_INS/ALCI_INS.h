#ifndef ALCI_INS_H
#define ALCI_INS_H

#include <ASMInstruction.h>



struct ALCI_INS : public ASMFramework::ASMInstruction
{
public:
	ALCI_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !ALCI_INS_H
