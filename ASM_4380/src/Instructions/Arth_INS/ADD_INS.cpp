#include "../../../include/Instructions/Arth_INS/ADD_INS.h"

#include <stdexcept>

ADD_INS::ADD_INS(): ASMInstruction("ADD")
{}

size_t ADD_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}