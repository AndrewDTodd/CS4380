#include "../../../include/Instructions/Heap_INS/ALCI_INS.h"

#include <stdexcept>

ALCI_INS::ALCI_INS() : ASMInstruction("ALCI")
{}

void ALCI_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}