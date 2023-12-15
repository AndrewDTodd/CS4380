#include "../../../include/Instructions/Jump_INS/BAL_INS.h"

#include <stdexcept>

BAL_INS::BAL_INS() : ASMInstruction("BAL")
{}

size_t BAL_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() < 1 || args.size() > 2)
		throw std::runtime_error("The BAL instruction expects either one argument, or two (BAL Label, BAL RD, Label), " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	if (args.size() == 1)
	{
		const int32_t opcode = 43;
		const std::string& labelName = args[0];

		size_t& offset = ASMFramework::ASMInstruction::GetLabelOffset(labelName, workpiece);

		SerializeToBuffer<int32_t>(buffer, opcode, static_cast<int32_t>(offset), 0);

		if (offset == 0)
			AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);
	}
	else
	{
		const int32_t opcode = 44;
		const std::string& labelName = args[1];

		int32_t registerID = langDef->GetRegisterID<int32_t>(args[0]);

		uint64_t& offset = GetLabelOffset(labelName, workpiece);

		CheckRegisterIDInvalid<int32_t, 16, 17, 18>(registerID);

		SerializeToBuffer<int32_t>(buffer, opcode, registerID, offset);

		if (offset == 0)
			AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

		CheckRegisterIDWarning<int32_t, 19, 20, 21>(registerID, sizeof(int32_t) * 3);
	}

	return sizeof(int32_t) * 3;
}