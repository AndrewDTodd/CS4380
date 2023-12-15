#include "../../../include/Instructions/Stack_INS/POP_INS.h"

#include <stdexcept>

POP_INS::POP_INS() : ASMInstruction("POP")
{}

size_t POP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The POP instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 41;
	const std::string& registerMnemonic = args[0];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);

	CheckRegisterIDInvalid<int32_t, 16, 17, 18>(id);

	SerializeToBuffer<int32_t>(buffer, opcode, id, 0);

	return sizeof(int32_t) * 3;
}