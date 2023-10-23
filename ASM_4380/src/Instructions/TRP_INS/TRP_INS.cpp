#include "../../../include/Instructions/TRP_INS/TRP_INS.h"

#include <stdexcept>

TRP_INS::TRP_INS() : ASMInstruction("TRP")
{}

size_t TRP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}