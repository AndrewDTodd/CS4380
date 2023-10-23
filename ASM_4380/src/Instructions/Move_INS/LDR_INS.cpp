#include "../../../include/Instructions/Move_INS/LDR_INS.h"

#include <stdexcept>

LDR_INS::LDR_INS() : ASMInstruction("LDR")
{}

size_t LDR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}