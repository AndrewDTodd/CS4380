#include "../../../include/Instructions/Logical_INS/AND_INS.h"

#include <stdexcept>

AND_INS::AND_INS() : ASMInstruction("AND")
{}

size_t AND_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}