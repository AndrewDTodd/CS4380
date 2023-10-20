#ifndef JMR_INS_H
#define JMR_INS_H

#include <ASMInstruction.h>

using namespace ASMFramework;

struct JMR_INS : public ASMFramework::ASMInstruction
{
public:
	JMR_INS();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !JMR_INS_H
