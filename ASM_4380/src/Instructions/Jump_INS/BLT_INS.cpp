#include "../../../include/Instructions/Jump_INS/BLT_INS.h"

#include <stdexcept>

BLT_INS::BLT_INS() : ASMInstruction("BLT")
{}

size_t BLT_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}