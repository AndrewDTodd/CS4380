#ifndef LDB_INS_H
#define LDB_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct LDB_INS : public ASMFramework::ASMInstruction
{
public:
	LDB_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !LDB_INS_H
