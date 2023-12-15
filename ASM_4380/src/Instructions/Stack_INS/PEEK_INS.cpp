#include "../../../include/Instructions/Stack_INS/PEEK_INS.h"

#include <stdexcept>

PEEK_INS::PEEK_INS() : ASMInstruction("PEEK")
{}

size_t PEEK_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The PEEK instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 42;
	const std::string& registerMnemonic = args[0];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);

	CheckRegisterIDInvalid<int32_t, 16, 17, 18>(id);

	SerializeToBuffer<int32_t>(buffer, opcode, id, 0);

	return sizeof(int32_t) * 3;
}