#include "../../../include/Instructions/Stack_INS/PUSH_INS.h"

#include <stdexcept>
#include <cstdint>

PUSH_INS::PUSH_INS() : ASMInstruction("PUSH")
{}

size_t PUSH_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The PUSH instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 40;
	const std::string& registerMnemonic = args[0];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);

	SerializeToBuffer<int32_t>(buffer, opcode, id, 0);

	return sizeof(int32_t) * 3;
}