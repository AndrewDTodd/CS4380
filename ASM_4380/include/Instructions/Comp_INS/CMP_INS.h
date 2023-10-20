#ifndef CMP_INS_H
#define CMP_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct CMP_INS : public ASMFramework::ASMInstruction
{
public:
	CMP_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !CMP_INS_H
