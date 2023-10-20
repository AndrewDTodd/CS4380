#include "../../../include/Instructions/Arth_INS/MUL_INS.h"

#include <stdexcept>

MUL_INS::MUL_INS() : ASMInstruction("MUL")
{}

void MUL_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}