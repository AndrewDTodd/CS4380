#include "../../../include/Instructions/Heap_INS/FREE_INS.h"

#include <stdexcept>

FREE_INS::FREE_INS() : ASMInstruction("FREE")
{}

size_t FREE_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}