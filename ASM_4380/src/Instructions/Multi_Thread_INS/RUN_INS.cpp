#include "../../../include/Instructions/Multi_Thread_INS/RUN_INS.h"

#include <stdexcept>

RUN_INS::RUN_INS() : ASMInstruction("RUN")
{}

void RUN_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}