#include "../../../include/Instructions/Heap_INS/FREE_INS.h"

#include <stdexcept>

FREE_INS::FREE_INS() : Instruction("FREE")
{}

void FREE_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}