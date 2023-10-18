#ifndef LDB_INS_H
#define LDB_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct LDB_INS : public ASMFramework::Instruction
{
public:
	LDB_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !LDB_INS_H
