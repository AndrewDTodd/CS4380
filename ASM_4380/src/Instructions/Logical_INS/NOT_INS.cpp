#include "../../../include/Instructions/Logical_INS/NOT_INS.h"

#include <stdexcept>

NOT_INS::NOT_INS() : ASMInstruction("NOT")
{}

size_t NOT_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}