#include "../../../include/Instructions/Move_INS/LDR_INS.h"

#include <stdexcept>

LDR_INS::LDR_INS() : ASMInstruction("LDR")
{}

size_t LDR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The LDR instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	//Label to register version
	if (workpiece->_symbolTable.contains(args[1]))
	{
		const int32_t opcode = 10;
		const std::string& labelName = args[1];

		int32_t registerID = langDef->GetRegisterID<int32_t>(args[0]);

		uint64_t& offset = GetLabelOffset(labelName, workpiece);

		CheckRegisterIDInvalid<int32_t, 16, 17, 18>(registerID);

		SerializeToBuffer<int32_t>(buffer, opcode, registerID, offset);

		if (offset == 0)
			AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

		CheckRegisterIDWarning<int32_t, 19, 20, 21>(registerID, sizeof(int32_t) * 3);
	}
	//Register to Register verison
	else
	{
		const int32_t opcode = 23;

		int32_t registerOneID = langDef->GetRegisterID<int32_t>(args[0]);
		int32_t registerTwoID = langDef->GetRegisterID<int32_t>(args[1]);

		CheckRegisterIDInvalid<int32_t, 16, 17, 18>(registerOneID);

		SerializeToBuffer<int32_t>(buffer, opcode, registerOneID, registerTwoID);

		CheckRegisterIDWarning<int32_t, 19, 20, 21>(registerOneID, sizeof(int32_t) * 3);
	}

	return sizeof(int32_t) * 3;
}