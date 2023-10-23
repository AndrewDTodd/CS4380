#include "../../../include/Instructions/Multi_Thread_INS/ULK_INS.h"

#include <stdexcept>

ULK_INS::ULK_INS() : ASMInstruction("ULK")
{}

size_t ULK_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}