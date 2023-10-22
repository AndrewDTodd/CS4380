#include "../../../include/Instructions/Arth_INS/ADD_INS.h"

#include <stdexcept>

ADD_INS::ADD_INS(): ASMInstruction("ADD")
{}

void ADD_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}