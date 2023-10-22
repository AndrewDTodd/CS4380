#include "../../../include/Instructions/Jump_INS/BNZ_INS.h"

#include <stdexcept>

BNZ_INS::BNZ_INS() : ASMInstruction("BNZ")
{}

void BNZ_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}