#include "../../../include/Instructions/Multi_Thread_INS/RUN_INS.h"
#include <stdexcept>

RUN_INS::RUN_INS() : ASMInstruction("RUN")
{}

size_t RUN_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The RUN instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 26;
	const std::string& labelName = args[1];

	int32_t id = langDef->GetRegisterID<int32_t>(args[0]);
	int64_t offset = GetLabelOffset(labelName, workpiece);

	CheckRegisterIDInvalid<int32_t, 16, 17, 18>(id);

	SerializeToBuffer<int32_t>(buffer, opcode, id, offset);

	if (offset == 0)
		AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

	CheckRegisterIDWarning<int32_t, 19, 20, 21>(id, sizeof(int32_t) * 3);

	return sizeof(int32_t) * 3;
}