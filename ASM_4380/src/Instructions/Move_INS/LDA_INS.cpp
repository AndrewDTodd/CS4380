#include "../../../include/Instructions/Move_INS/LDA_INS.h"
#include <stdexcept>

LDA_INS::LDA_INS() : ASMInstruction("LDA")
{}

size_t LDA_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}