#include "../../../include/Instructions/Multi_Thread_INS/ULK_INS.h"

#include <stdexcept>
#include <cstdint>

ULK_INS::ULK_INS() : ASMInstruction("ULK")
{}

size_t ULK_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The ULK instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 30;
	const std::string& labelName = args[0];

	uint64_t& offset = ASMFramework::ASMInstruction::GetLabelOffset(labelName, workpiece);

	SerializeToBuffer<int32_t>(buffer, opcode, static_cast<int32_t>(offset));

	if (offset == 0)
		AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

	SerializeToBuffer<int32_t>(buffer, 0);

	return sizeof(int32_t) * 3;
}