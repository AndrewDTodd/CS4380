#include "../../../include/Instructions/Move_INS/MOV_INS.h"

#include <stdexcept>

MOV_INS::MOV_INS() : ASMInstruction("MOV")
{}

void MOV_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}