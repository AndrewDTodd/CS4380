#include "../../../include/Instructions/Multi_Thread_INS/END_INS.h"
#include <stdexcept>

END_INS::END_INS() : ASMInstruction("END")
{}

size_t END_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 0)
		throw std::runtime_error("The END instruction expects no arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 28;

	SerializeToBuffer<int32_t>(buffer, opcode, 0, 0);

	return sizeof(int32_t) * 3;
}