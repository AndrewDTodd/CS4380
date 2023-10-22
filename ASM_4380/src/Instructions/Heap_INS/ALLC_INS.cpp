#include "../../../include/Instructions/Heap_INS/ALLC_INS.h"

#include <stdexcept>

ALLC_INS::ALLC_INS() : ASMInstruction("ALLC")
{}

void ALLC_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}