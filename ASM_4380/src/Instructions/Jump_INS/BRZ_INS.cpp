#include "../../../include/Instructions/Jump_INS/BRZ_INS.h"

#include <stdexcept>

BRZ_INS::BRZ_INS() : ASMInstruction("BRZ")
{}

size_t BRZ_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}