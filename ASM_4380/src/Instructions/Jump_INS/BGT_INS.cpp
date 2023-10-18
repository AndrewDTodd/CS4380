#include "../../../include/Instructions/Jump_INS/BGT_INS.h"

#include <stdexcept>

BGT_INS::BGT_INS() : Instruction("BGT")
{}

void BGT_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}