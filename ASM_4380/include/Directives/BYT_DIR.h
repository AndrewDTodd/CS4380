#ifndef BYT_DIR_H
#define BYT_DIR_H

#include <ASMDirective.h>

using namespace ASMFramework;

struct BYT_DIR : public ASMFramework::ASMDirective
{
public:
	BYT_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !BYT_DIR_H
