#include "../../../include/Instructions/Logical_INS/OR_INS.h"

#include <stdexcept>

OR_INS::OR_INS() : Instruction("OR")
{}

void OR_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}