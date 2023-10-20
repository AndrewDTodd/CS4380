#include "../../include/Directives/STR_DIR.h"

STR_DIR::STR_DIR(): ASMDirective(".STR")
{}

void STR_DIR::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}