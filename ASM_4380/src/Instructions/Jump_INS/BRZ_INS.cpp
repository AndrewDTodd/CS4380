#include "../../../include/Instructions/Jump_INS/BRZ_INS.h"

#include <stdexcept>

BRZ_INS::BRZ_INS() : Instruction("BRZ")
{}

void BRZ_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}