#include "../../../include/Instructions/Arth_INS/SUB_INS.h"

#include <stdexcept>

SUB_INS::SUB_INS() : ASMInstruction("SUB")
{}

size_t SUB_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}