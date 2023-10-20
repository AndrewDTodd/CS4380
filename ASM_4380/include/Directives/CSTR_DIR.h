#ifndef CSTR_DIR_H
#define CSTR_DIR_H

#include <ASMDirective.h>

using namespace ASMFramework;

struct CSTR_DIR : public ASMFramework::ASMDirective
{
public:
	CSTR_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !CSTR_DIR_H
