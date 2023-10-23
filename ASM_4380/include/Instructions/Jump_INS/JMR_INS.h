#ifndef JMR_INS_H
#define JMR_INS_H

#include <ASMInstruction.h>



struct JMR_INS : public ASMFramework::ASMInstruction
{
public:
	JMR_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !JMR_INS_H
