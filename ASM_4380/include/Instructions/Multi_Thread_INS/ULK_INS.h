#ifndef ULK_INS_H
#define ULK_INS_H

#include <ASMInstruction.h>



struct ULK_INS : public ASMFramework::ASMInstruction
{
public:
	ULK_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !ULK_INS_H
