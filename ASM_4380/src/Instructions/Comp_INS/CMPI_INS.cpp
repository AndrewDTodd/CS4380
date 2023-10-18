#include "../../../include/Instructions/Comp_INS/CMPI_INS.h"

#include <stdexcept>

CMPI_INS::CMPI_INS() : Instruction("CMPI")
{}

void CMPI_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}