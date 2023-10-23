#include "../../../include/Instructions/Move_INS/STR_INS.h"

#include <stdexcept>

STR_INS::STR_INS() : ASMInstruction("STR")
{}

size_t STR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}