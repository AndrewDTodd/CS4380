#ifndef LDB_INS_H
#define LDB_INS_H

#include <ASMInstruction.h>



struct LDB_INS : public ASMFramework::ASMInstruction
{
public:
	LDB_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !LDB_INS_H
