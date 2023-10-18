#include "../../../include/Instructions/Heap_INS/ALCI_INS.h"

#include <stdexcept>

ALCI_INS::ALCI_INS() : Instruction("ALCI")
{}

void ALCI_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}