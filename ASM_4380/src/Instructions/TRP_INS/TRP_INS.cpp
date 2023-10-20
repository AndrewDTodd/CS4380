#include "../../../include/Instructions/TRP_INS/TRP_INS.h"

#include <stdexcept>

TRP_INS::TRP_INS() : ASMInstruction("TRP")
{}

void TRP_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}