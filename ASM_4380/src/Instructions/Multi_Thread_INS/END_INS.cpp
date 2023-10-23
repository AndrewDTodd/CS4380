#include "../../../include/Instructions/Multi_Thread_INS/END_INS.h"

#include <stdexcept>

END_INS::END_INS() : ASMInstruction("END")
{}

size_t END_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}