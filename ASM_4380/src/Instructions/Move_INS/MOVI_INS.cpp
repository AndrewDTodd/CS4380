#include "../../../include/Instructions/Move_INS/MOVI_INS.h"

#include <stdexcept>

MOVI_INS::MOVI_INS() : ASMInstruction("MOVI")
{}

void MOVI_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}