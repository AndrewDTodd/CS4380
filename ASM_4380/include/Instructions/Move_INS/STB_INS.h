#ifndef STB_INS_H
#define STB_INS_H

#include <ASMInstruction.h>



struct STB_INS : public ASMFramework::ASMInstruction
{
public:
	STB_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !STB_INS_H
