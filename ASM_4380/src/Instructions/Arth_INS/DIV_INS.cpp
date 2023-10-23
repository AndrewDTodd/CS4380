#include "../../../include/Instructions/Arth_INS/DIV_INS.h"

#include <stdexcept>

DIV_INS::DIV_INS() : ASMInstruction("DIV")
{}

size_t DIV_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}