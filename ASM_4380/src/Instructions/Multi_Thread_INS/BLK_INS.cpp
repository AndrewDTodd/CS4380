#include "../../../include/Instructions/Multi_Thread_INS/BLK_INS.h"

#include <stdexcept>

BLK_INS::BLK_INS() : ASMInstruction("BLK")
{}

void BLK_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}