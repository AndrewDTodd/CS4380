#include "../../../include/Instructions/Move_INS/STB_INS.h"

#include <stdexcept>

STB_INS::STB_INS() : ASMInstruction("STB")
{}

void STB_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}