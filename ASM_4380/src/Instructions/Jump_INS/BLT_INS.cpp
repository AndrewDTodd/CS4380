#include "../../../include/Instructions/Jump_INS/BLT_INS.h"

#include <stdexcept>

BLT_INS::BLT_INS() : Instruction("BLT")
{}

void BLT_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}