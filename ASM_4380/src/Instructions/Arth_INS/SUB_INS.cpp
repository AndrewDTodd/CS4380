#include "../../../include/Instructions/Arth_INS/SUB_INS.h"

#include <stdexcept>

SUB_INS::SUB_INS() : ASMInstruction("SUB")
{}

void SUB_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}