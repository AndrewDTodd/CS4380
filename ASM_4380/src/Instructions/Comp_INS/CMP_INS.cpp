#include "../../../include/Instructions/Comp_INS/CMP_INS.h"

#include <stdexcept>

CMP_INS::CMP_INS() : ASMInstruction("CMP")
{}

void CMP_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}