#include "../../../include/Instructions/Multi_Thread_INS/LCK_INS.h"

#include <stdexcept>

LCK_INS::LCK_INS() : ASMInstruction("LCK")
{}

void LCK_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}