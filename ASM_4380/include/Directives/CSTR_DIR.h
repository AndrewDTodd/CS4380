#ifndef CSTR_DIR_H
#define CSTR_DIR_H

#include <ASMDirective.h>

struct CSTR_DIR : public ASMFramework::ASMDirective
{
public:
	CSTR_DIR();

	size_t Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !CSTR_DIR_H
