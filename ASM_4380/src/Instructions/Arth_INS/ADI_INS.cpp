#include "../../../include/Instructions/Arth_INS/ADI_INS.h"

#include <stdexcept>

ADI_INS::ADI_INS() : ASMInstruction("ADI")
{}

size_t ADI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}