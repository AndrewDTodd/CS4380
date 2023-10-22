#include "../../include/Directives/BYT_DIR.h"

#include <stdexcept>

BYT_DIR::BYT_DIR(): ASMDirective(".BYT")
{}

void BYT_DIR::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}