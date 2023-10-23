#include "../../../include/Instructions/Jump_INS/BGT_INS.h"

#include <stdexcept>

BGT_INS::BGT_INS() : ASMInstruction("BGT")
{}

size_t BGT_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}