#include "../../../include/Instructions/Logical_INS/OR_INS.h"

#include <stdexcept>

OR_INS::OR_INS() : ASMInstruction("OR")
{}

void OR_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}