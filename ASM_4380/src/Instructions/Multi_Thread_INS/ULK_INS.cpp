#include "../../../include/Instructions/Multi_Thread_INS/ULK_INS.h"

#include <stdexcept>

ULK_INS::ULK_INS() : ASMInstruction("ULK")
{}

void ULK_INS::Implementation(const ASMFramework::Workpiece* const& workpiece) const
{
	throw NotImplemented();
}