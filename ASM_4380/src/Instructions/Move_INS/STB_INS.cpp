#include "../../../include/Instructions/Move_INS/STB_INS.h"

#include <stdexcept>

STB_INS::STB_INS() : ASMInstruction("STB")
{}

size_t STB_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}