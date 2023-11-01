#include "../../../include/Instructions/Multi_Thread_INS/RUN_INS.h"

#include <stdexcept>

RUN_INS::RUN_INS() : ASMInstruction("RUN")
{}

size_t RUN_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
	throw NotImplemented();
}