#include "../../../include/Instructions/Move_INS/LDR_INS.h"

#include <stdexcept>

LDR_INS::LDR_INS() : ASMInstruction("LDR")
{}

size_t LDR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The .LDR instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	//Label to register version
	if (workpiece->_symbolTable.contains(args[1]))
	{
		const int32_t opcode = 10;
		const std::string& labelName = args[1];

		int32_t registerID = GetRegisterID<int32_t>(args[0], 0, 15);

		uint64_t& offset = GetLabelOffset(args[2], workpiece);

		SerializeToBuffer<int32_t>(buffer, opcode, registerID, offset);

		if (offset == 0)
			AddUnresolvedLabel(labelName, buffer, workpiece);
	}
	//Register to Register verison
	else
	{
		const int32_t opcode = 23;

		int32_t registerOneID = GetRegisterID<int32_t>(args[0], 0, 15);
		int32_t registerTwoID = GetRegisterID<int32_t>(args[1], 0, 15);

		SerializeToBuffer<int32_t>(buffer, opcode, registerOneID, registerTwoID);
	}

	return sizeof(int32_t) * 3;
}