#include "../../../include/Instructions/Heap_INS/FREE_INS.h"

#include <stdexcept>

FREE_INS::FREE_INS() : ASMInstruction("FREE")
{}

size_t FREE_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The FREE instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 38;
	const std::string& registerMnemonic = args[0];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);

	SerializeToBuffer<int32_t>(buffer, opcode, id, 0);

	CheckRegisterIDWarning<int32_t, 16, 17, 18, 19, 20, 21>(id, sizeof(int32_t) * 3);

	return sizeof(int32_t) * 3;
}