#include "../../../include/Instructions/Move_INS/LDB_INS.h"

#include <stdexcept>

LDB_INS::LDB_INS() : ASMInstruction("LDB")
{}

void LDB_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}