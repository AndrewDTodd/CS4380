#ifndef BYT_DIR_H
#define BYT_DIR_H

#include <ASMDirective.h>

struct BYT_DIR : public ASMFramework::ASMDirective
{
public:
	BYT_DIR();

	void Implementation(const ASMFramework::Workpiece* const& workpiece) const override;
};
#endif // !BYT_DIR_H
