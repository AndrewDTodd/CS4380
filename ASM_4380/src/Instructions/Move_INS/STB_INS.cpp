#include "../../../include/Instructions/Move_INS/STB_INS.h"

#include <stdexcept>

STB_INS::STB_INS() : ASMInstruction("STB")
{}

size_t STB_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The .STB instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	//Register to label version
	if (workpiece->_symbolTable.contains(args[1]))
	{
		const int32_t opcode = 11;
		const std::string& labelName = args[1];

		int32_t registerID = langDef->GetRegisterID<int32_t>(args[0]);

		uint64_t& offset = GetLabelOffset(labelName, workpiece);

		SerializeToBuffer<int32_t>(buffer, opcode, registerID, offset);

		if (offset == 0)
			AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);
	}
	//Register to Register verison
	else
	{
		const int32_t opcode = 24;

		int32_t registerOneID = langDef->GetRegisterID<int32_t>(args[0]);
		int32_t registerTwoID = langDef->GetRegisterID<int32_t>(args[1]);

		SerializeToBuffer<int32_t>(buffer, opcode, registerOneID, registerTwoID);
	}

	return sizeof(int32_t) * 3;
}