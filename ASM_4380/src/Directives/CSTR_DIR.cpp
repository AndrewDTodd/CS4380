#include "../../include/Directives/CSTR_DIR.h"

#include <stdexcept>

CSTR_DIR::CSTR_DIR(): ASMDirective(".CSTR")
{}

void CSTR_DIR::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}