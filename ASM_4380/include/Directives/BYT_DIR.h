#ifndef BYT_DIR_H
#define BYT_DIR_H

#include <ASMDirective.h>

struct BYT_DIR : public ASMFramework::ASMDirective
{
public:
	BYT_DIR();

	size_t Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const override;
};
#endif // !BYT_DIR_H
