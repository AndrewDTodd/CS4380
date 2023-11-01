#include "../../../include/Instructions/Heap_INS/ALCI_INS.h"

#include <stdexcept>

ALCI_INS::ALCI_INS() : ASMInstruction("ALCI")
{}

size_t ALCI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}