#ifndef STR_DIR_H
#define STR_DIR_H

#include <ASMDirective.h>

struct STR_DIR: public ASMFramework::ASMDirective
{
public:
	STR_DIR();

	size_t Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !STR_DIR_H
