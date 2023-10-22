#include "../../include/Directives/STR_DIR.h"

#include <stdexcept>

STR_DIR::STR_DIR(): ASMDirective(".STR")
{}

void STR_DIR::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}