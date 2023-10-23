#include "../../../include/Instructions/Comp_INS/CMPI_INS.h"

#include <stdexcept>

CMPI_INS::CMPI_INS() : ASMInstruction("CMPI")
{}

size_t CMPI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}