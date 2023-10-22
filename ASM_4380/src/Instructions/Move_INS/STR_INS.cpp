#include "../../../include/Instructions/Move_INS/STR_INS.h"

#include <stdexcept>

STR_INS::STR_INS() : ASMInstruction("STR")
{}

void STR_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}