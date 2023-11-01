#include "../../../include/Instructions/Move_INS/LDA_INS.h"
#include <stdexcept>

LDA_INS::LDA_INS() : ASMInstruction("LDA")
{}

size_t LDA_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The LDA instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 8;
	const std::string& labelName = args[1];

	int32_t id = langDef->GetRegisterID<int32_t>(args[0]);
	int64_t offset = GetLabelOffset(labelName, workpiece);

	SerializeToBuffer<int32_t>(buffer, opcode, id, offset);

	if (offset == 0)
		AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

	return sizeof(int32_t) * 3;
}