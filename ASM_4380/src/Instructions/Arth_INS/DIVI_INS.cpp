#include "../../../include/Instructions/Arth_INS/DIVI_INS.h"

#include <stdexcept>

DIVI_INS::DIVI_INS() : Instruction("DIVI")
{}

void DIVI_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}