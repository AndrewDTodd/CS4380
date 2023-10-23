#include "../../../include/Instructions/Move_INS/MOVI_INS.h"

#include <stdexcept>

MOVI_INS::MOVI_INS() : ASMInstruction("MOVI")
{}

size_t MOVI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}