#include "../../../include/Instructions/Arth_INS/SUB_INS.h"

#include <stdexcept>

SUB_INS::SUB_INS() : Instruction("SUB")
{}

void SUB_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}