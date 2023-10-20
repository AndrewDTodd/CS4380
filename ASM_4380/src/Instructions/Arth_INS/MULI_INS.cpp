#include "../../../include/Instructions/Arth_INS/MULI_INS.h"

#include <stdexcept>

MULI_INS::MULI_INS() : ASMInstruction("MULI")
{}

void MULI_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}