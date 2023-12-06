#include "../../../include/Instructions/Jump_INS/BAL_INS.h"

#include <stdexcept>

BAL_INS::BAL_INS() : ASMInstruction("BAL")
{}

size_t BAL_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The BAL instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 43;
	const std::string& labelName = args[0];

	size_t& offset = ASMFramework::ASMInstruction::GetLabelOffset(labelName, workpiece);

	SerializeToBuffer<int32_t>(buffer, opcode, static_cast<int32_t>(offset), 0);

	if (offset == 0)
		AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

	return sizeof(int32_t) * 3;
}