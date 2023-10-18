#ifndef JMR_INS_H
#define JMR_INS_H

#include <Instruction.h>

using namespace ASMFramework;

struct JMR_INS : public ASMFramework::Instruction
{
public:
	JMR_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !JMR_INS_H
