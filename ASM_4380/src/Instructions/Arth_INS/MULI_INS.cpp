#include "../../../include/Instructions/Arth_INS/MULI_INS.h"

#include <stdexcept>

MULI_INS::MULI_INS() : ASMInstruction("MULI")
{}

size_t MULI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}