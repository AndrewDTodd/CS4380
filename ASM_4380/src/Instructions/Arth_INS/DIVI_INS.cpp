#include "../../../include/Instructions/Arth_INS/DIVI_INS.h"

#include <stdexcept>

DIVI_INS::DIVI_INS() : ASMInstruction("DIVI")
{}

size_t DIVI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}