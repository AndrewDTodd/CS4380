#include "../../include/Directives/CSTR_DIR.h"

CSTR_DIR::CSTR_DIR(): Directive(".CSTR")
{}

void CSTR_DIR::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}