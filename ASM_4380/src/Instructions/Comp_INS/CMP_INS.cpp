#include "../../../include/Instructions/Comp_INS/CMP_INS.h"

#include <stdexcept>

CMP_INS::CMP_INS() : Instruction("CMP")
{}

void CMP_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}