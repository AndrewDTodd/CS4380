#ifndef INT_DIR_H
#define INT_DIR_H

#include <Directive.h>

using namespace ASMFramework;

struct INT_DIR : public ASMFramework::Directive
{
public:
	INT_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !INT_DIR_H
