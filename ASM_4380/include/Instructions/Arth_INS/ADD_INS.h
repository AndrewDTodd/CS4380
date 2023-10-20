#ifndef ADD_INS_H
#define ADD_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct ADD_INS : public ASMFramework::ASMInstruction
{
public:
	ADD_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !ADD_INS_H
