#ifndef END_INS_H
#define END_INS_H

#include <ASMInstruction.h>



struct END_INS : public ASMFramework::ASMInstruction
{
public:
	END_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !END_INS_H
