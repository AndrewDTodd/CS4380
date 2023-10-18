#include "../../../include/Instructions/Multi_Thread_INS/END_INS.h"

#include <stdexcept>

END_INS::END_INS() : Instruction("END")
{}

void END_INS::Implementation(const Workpiece* const& workpiece) const
{
	throw NotImplemented();
}