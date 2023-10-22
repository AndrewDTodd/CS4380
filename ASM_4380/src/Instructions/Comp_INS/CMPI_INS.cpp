#include "../../../include/Instructions/Comp_INS/CMPI_INS.h"

#include <stdexcept>

CMPI_INS::CMPI_INS() : ASMInstruction("CMPI")
{}

void CMPI_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}