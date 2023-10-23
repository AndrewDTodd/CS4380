#include "../../../include/Instructions/Move_INS/LDB_INS.h"

#include <stdexcept>

LDB_INS::LDB_INS() : ASMInstruction("LDB")
{}

size_t LDB_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}