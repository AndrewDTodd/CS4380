#ifndef RUN_INS_H
#define RUN_INS_H

#include <ASMInstruction.h>



struct RUN_INS : public ASMFramework::ASMInstruction
{
public:
	RUN_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !RUN_INS_H
