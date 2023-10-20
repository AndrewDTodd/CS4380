#include "../../../include/Instructions/Jump_INS/JMP_INS.h"

#include <stdexcept>

JMP_INS::JMP_INS() : ASMInstruction("JMP")
{}

void JMP_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}