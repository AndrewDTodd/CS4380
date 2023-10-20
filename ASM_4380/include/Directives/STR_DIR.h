#ifndef STR_DIR_H
#define STR_DIR_H

#include <ASMDirective.h>

using namespace ASMFramework;

struct STR_DIR: public ASMFramework::ASMDirective
{
public:
	STR_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !STR_DIR_H
