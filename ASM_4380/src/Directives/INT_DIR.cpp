#include "../../include/Directives/INT_DIR.h"

INT_DIR::INT_DIR(): ASMDirective(".INT")
{}

void INT_DIR::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}