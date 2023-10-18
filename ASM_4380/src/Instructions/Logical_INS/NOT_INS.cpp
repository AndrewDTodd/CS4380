#include "../../../include/Instructions/Logical_INS/NOT_INS.h"

#include <stdexcept>

NOT_INS::NOT_INS() : Instruction("NOT")
{}

void NOT_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}