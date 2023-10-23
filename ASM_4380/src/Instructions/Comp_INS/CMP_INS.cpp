#include "../../../include/Instructions/Comp_INS/CMP_INS.h"

#include <stdexcept>

CMP_INS::CMP_INS() : ASMInstruction("CMP")
{}

size_t CMP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}