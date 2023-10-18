#ifndef CSTR_DIR_H
#define CSTR_DIR_H

#include <Directive.h>

using namespace ASMFramework;

struct CSTR_DIR : public ASMFramework::Directive
{
public:
	CSTR_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !CSTR_DIR_H
