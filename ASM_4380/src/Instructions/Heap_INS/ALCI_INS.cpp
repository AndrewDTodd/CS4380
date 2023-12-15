#include "../../../include/Instructions/Heap_INS/ALCI_INS.h"

#include <stdexcept>

ALCI_INS::ALCI_INS() : ASMInstruction("ALCI")
{}

size_t ALCI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The ALCI instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 14;

	int32_t id = langDef->GetRegisterID<int32_t>(args[0]);
	int32_t immediate = GetImmediateValue<int32_t>(args[1]);

	CheckRegisterIDInvalid<int32_t, 16, 17, 18>(id);

	SerializeToBuffer<int32_t>(buffer, opcode, id, immediate);

	CheckRegisterIDWarning<int32_t, 19, 20, 21>(id, sizeof(int32_t) * 2);

	return sizeof(int32_t) * 3;
}