#include "../../../include/Instructions/Heap_INS/ALLC_INS.h"

#include <stdexcept>

ALLC_INS::ALLC_INS() : Instruction("ALLC")
{}

void ALLC_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}