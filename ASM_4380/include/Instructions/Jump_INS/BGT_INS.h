#ifndef BGT_INS_H
#define BGT_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct BGT_INS : public ASMFramework::ASMInstruction
{
public:
	BGT_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !JMP_INS_H
