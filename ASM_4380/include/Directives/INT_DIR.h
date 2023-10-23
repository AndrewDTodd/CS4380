#ifndef INT_DIR_H
#define INT_DIR_H

#include <ASMDirective.h>

struct INT_DIR : public ASMFramework::ASMDirective
{
public:
	INT_DIR();

	size_t Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !INT_DIR_H
