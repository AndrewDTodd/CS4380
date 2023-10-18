#include "../../../include/Instructions/Move_INS/LDA_INS.h"
#include <stdexcept>

LDA_INS::LDA_INS() : Instruction("LDA")
{}

void LDA_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}