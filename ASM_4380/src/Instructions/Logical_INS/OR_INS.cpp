#include "../../../include/Instructions/Logical_INS/OR_INS.h"

#include <stdexcept>

OR_INS::OR_INS() : ASMInstruction("OR")
{}

size_t OR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}