#include "../../../include/Instructions/Arth_INS/DIV_INS.h"

#include <stdexcept>

DIV_INS::DIV_INS() : ASMInstruction("DIV")
{}

void DIV_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}