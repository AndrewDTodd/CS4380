#include "../../../include/Instructions/Move_INS/LDR_INS.h"

#include <stdexcept>

LDR_INS::LDR_INS() : ASMInstruction("LDR")
{}

void LDR_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}