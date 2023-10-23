#include "../../../include/Instructions/Multi_Thread_INS/BLK_INS.h"

#include <stdexcept>

BLK_INS::BLK_INS() : ASMInstruction("BLK")
{}

size_t BLK_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}