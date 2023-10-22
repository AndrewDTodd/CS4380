#include "../../../include/Instructions/Logical_INS/AND_INS.h"

#include <stdexcept>

AND_INS::AND_INS() : ASMInstruction("AND")
{}

void AND_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}