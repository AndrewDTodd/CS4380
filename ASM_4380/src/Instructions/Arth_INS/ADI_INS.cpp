#include "../../../include/Instructions/Arth_INS/ADI_INS.h"

#include <stdexcept>

ADI_INS::ADI_INS() : Instruction("ADI")
{}

void ADI_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}