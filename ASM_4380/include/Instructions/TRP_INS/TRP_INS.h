#ifndef TRP_INS_H
#define TRP_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct TRP_INS : public ASMFramework::ASMInstruction
{
public:
	TRP_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !TRP_INS_H
