#include "../../../include/Instructions/Arth_INS/DIV_INS.h"

#include <stdexcept>

DIV_INS::DIV_INS() : ASMInstruction("DIV")
{}

size_t DIV_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The DIV instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 17;

	int32_t registerIdOne = langDef->GetRegisterID<int32_t>(args[0]);
	int32_t registerIdTwo = langDef->GetRegisterID<int32_t>(args[1]);

	if (registerIdOne > 15)
		throw std::runtime_error("You may not set the value of special registers this way. \"" + args[0] + "\" is not valid in this context. R0 - R15 are valid");

	SerializeToBuffer<int32_t>(buffer, opcode, registerIdOne, registerIdTwo);

	return sizeof(int32_t) * 3;
}