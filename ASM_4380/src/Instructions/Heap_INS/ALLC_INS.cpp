#include "../../../include/Instructions/Heap_INS/ALLC_INS.h"

#include <stdexcept>

ALLC_INS::ALLC_INS() : ASMInstruction("ALLC")
{}

size_t ALLC_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}