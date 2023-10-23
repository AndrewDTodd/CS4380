#include "../../../include/Instructions/Arth_INS/MUL_INS.h"

#include <stdexcept>

MUL_INS::MUL_INS() : ASMInstruction("MUL")
{}

size_t MUL_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}