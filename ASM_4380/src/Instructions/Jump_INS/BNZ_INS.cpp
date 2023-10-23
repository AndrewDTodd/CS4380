#include "../../../include/Instructions/Jump_INS/BNZ_INS.h"

#include <stdexcept>

BNZ_INS::BNZ_INS() : ASMInstruction("BNZ")
{}

size_t BNZ_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}