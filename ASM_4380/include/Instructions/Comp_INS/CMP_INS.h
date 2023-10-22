#ifndef CMP_INS_H
#define CMP_INS_H

#include <ASMInstruction.h>



struct CMP_INS : public ASMFramework::ASMInstruction
{
public:
	CMP_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !CMP_INS_H
