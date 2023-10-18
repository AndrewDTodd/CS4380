#include "../../../include/Instructions/Logical_INS/AND_INS.h"

#include <stdexcept>

AND_INS::AND_INS() : Instruction("AND")
{}

void AND_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}