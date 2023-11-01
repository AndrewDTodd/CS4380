#include "../../../include/Instructions/Comp_INS/CMPI_INS.h"

#include <stdexcept>

CMPI_INS::CMPI_INS() : ASMInstruction("CMPI")
{}

size_t CMPI_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The CMPI instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 32;

	int32_t id = langDef->GetRegisterID<int32_t>(args[0]);
	int32_t immediate = GetImmediateValue<int32_t>(args[1]);

	if (id > 15)
		throw std::runtime_error("You may not set the value of special registers this way. \"" + args[0] + "\" is not valid in this context. R0 - R15 are valid");

	SerializeToBuffer<int32_t>(buffer, opcode, id, immediate);

	return sizeof(int32_t) * 3;
}