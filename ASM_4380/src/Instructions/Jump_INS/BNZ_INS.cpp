#include "../../../include/Instructions/Jump_INS/BNZ_INS.h"

#include <stdexcept>

BNZ_INS::BNZ_INS() : Instruction("BNZ")
{}

void BNZ_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}