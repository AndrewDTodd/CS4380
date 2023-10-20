#ifndef OR_INS_H
#define OR_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct OR_INS : public ASMFramework::ASMInstruction
{
public:
	OR_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !OR_INS_H
