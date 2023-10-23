#include "../../include/Directives/CSTR_DIR.h"

#include <stdexcept>

CSTR_DIR::CSTR_DIR(): ASMDirective(".CSTR")
{}

size_t CSTR_DIR::Implementation(ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}