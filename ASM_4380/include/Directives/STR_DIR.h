#ifndef STR_DIR_H
#define STR_DIR_H

#include <Directive.h>

using namespace ASMFramework;

struct STR_DIR: public ASMFramework::Directive
{
public:
	STR_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !STR_DIR_H
