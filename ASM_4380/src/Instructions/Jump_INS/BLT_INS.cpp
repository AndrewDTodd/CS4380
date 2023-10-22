#include "../../../include/Instructions/Jump_INS/BLT_INS.h"

#include <stdexcept>

BLT_INS::BLT_INS() : ASMInstruction("BLT")
{}

void BLT_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}