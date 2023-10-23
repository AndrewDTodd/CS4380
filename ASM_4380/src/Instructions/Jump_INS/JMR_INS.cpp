#include "../../../include/Instructions/Jump_INS/JMR_INS.h"

#include <stdexcept>

JMR_INS::JMR_INS() : ASMInstruction("JMR")
{}

size_t JMR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}