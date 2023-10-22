#include "../../../include/Instructions/Jump_INS/BGT_INS.h"

#include <stdexcept>

BGT_INS::BGT_INS() : ASMInstruction("BGT")
{}

void BGT_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}