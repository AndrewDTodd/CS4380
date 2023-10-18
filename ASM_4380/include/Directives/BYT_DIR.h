#ifndef BYT_DIR_H
#define BYT_DIR_H

#include <Directive.h>

using namespace ASMFramework;

struct BYT_DIR : public ASMFramework::Directive
{
public:
	BYT_DIR();

	void Implementation(const Workpiece* const& workpiece) const override;
};
#endif // !BYT_DIR_H
