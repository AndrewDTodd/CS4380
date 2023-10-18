#include "../../../include/Instructions/Move_INS/STB_INS.h"

#include <stdexcept>

STB_INS::STB_INS() : Instruction("STB")
{}

void STB_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}