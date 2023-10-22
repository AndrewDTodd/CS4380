#ifndef INT_DIR_H
#define INT_DIR_H

#include <ASMDirective.h>

struct INT_DIR : public ASMFramework::ASMDirective
{
public:
	INT_DIR();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !INT_DIR_H
