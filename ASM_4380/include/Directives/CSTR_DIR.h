#ifndef CSTR_DIR_H
#define CSTR_DIR_H

#include <ASMDirective.h>

struct CSTR_DIR : public ASMFramework::ASMDirective
{
public:
	CSTR_DIR();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !CSTR_DIR_H
