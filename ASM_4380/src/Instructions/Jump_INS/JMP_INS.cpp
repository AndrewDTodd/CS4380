#include "../../../include/Instructions/Jump_INS/JMP_INS.h"

#include <stdexcept>
#include <cstdint>

JMP_INS::JMP_INS() : ASMInstruction("JMP")
{}

size_t JMP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The .JMP instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 1;
	const std::string& labelName = args[0];

	uint64_t& offset = ASMFramework::ASMInstruction::GetLabelOffset(labelName, workpiece);

	SerializeToBuffer<int32_t>(buffer, opcode, static_cast<int32_t>(offset));

	if (offset == 0)
		AddUnresolvedLabel(labelName, buffer, workpiece);

	SerializeToBuffer<int32_t>(buffer, 0);

	return sizeof(int32_t) * 3;
}