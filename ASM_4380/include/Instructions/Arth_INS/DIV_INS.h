#ifndef DIV_INS_H
#define DIV_INS_H

#include <ASMInstruction.h>



struct DIV_INS : public ASMFramework::ASMInstruction
{
public:
	DIV_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !DIV_INS_H
