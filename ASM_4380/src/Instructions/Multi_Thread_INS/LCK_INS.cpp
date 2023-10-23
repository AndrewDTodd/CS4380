#include "../../../include/Instructions/Multi_Thread_INS/LCK_INS.h"

#include <stdexcept>

LCK_INS::LCK_INS() : ASMInstruction("LCK")
{}

size_t LCK_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}