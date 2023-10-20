#ifndef STB_INS_H
#define STB_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct STB_INS : public ASMFramework::ASMInstruction
{
public:
	STB_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !STB_INS_H
