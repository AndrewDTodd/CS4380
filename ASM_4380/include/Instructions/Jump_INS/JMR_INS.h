#ifndef JMR_INS_H
#define JMR_INS_H

#include <ASMInstruction.h>



struct JMR_INS : public ASMFramework::ASMInstruction
{
public:
	JMR_INS();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !JMR_INS_H
