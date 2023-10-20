#ifndef DIV_INS_H
#define DIV_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct DIV_INS : public ASMFramework::ASMInstruction
{
public:
	DIV_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !DIV_INS_H
