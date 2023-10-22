#ifndef LDA_INS_H
#define LDA_INS_H

#include <ASMInstruction.h>



struct LDA_INS : public ASMFramework::ASMInstruction
{
public:
	LDA_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !LDA_INS_H
