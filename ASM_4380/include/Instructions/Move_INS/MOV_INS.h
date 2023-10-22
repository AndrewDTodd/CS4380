#ifndef MOV_INS_H
#define MOV_INS_H

#include <ASMInstruction.h>



struct MOV_INS : public ASMFramework::ASMInstruction
{
public:
	MOV_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !MOV_INS_H
