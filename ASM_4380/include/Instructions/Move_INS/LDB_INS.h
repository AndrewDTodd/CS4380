#ifndef LDB_INS_H
#define LDB_INS_H

#include <ASMInstruction.h>



struct LDB_INS : public ASMFramework::ASMInstruction
{
public:
	LDB_INS();

	size_t Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !LDB_INS_H
