#include "../../../include/Instructions/Heap_INS/FREE_INS.h"

#include <stdexcept>

FREE_INS::FREE_INS() : ASMInstruction("FREE")
{}

void FREE_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}