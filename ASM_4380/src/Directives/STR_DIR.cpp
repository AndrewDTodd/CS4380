#include "../../include/Directives/STR_DIR.h"

#include <stdexcept>

STR_DIR::STR_DIR(): ASMDirective(".STR")
{}

size_t STR_DIR::Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}