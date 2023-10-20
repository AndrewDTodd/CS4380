#include "../../../include/Instructions/Jump_INS/JMR_INS.h"

#include <stdexcept>

JMR_INS::JMR_INS() : ASMInstruction("JMR")
{}

void JMR_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}