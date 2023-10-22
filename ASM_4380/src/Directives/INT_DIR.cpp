#include "../../include/Directives/INT_DIR.h"

#include <stdexcept>

INT_DIR::INT_DIR(): ASMDirective(".INT")
{}

void INT_DIR::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}