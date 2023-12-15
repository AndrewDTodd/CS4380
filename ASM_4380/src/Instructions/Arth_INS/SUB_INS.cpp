#include "../../../include/Instructions/Arth_INS/SUB_INS.h"

#include <stdexcept>

SUB_INS::SUB_INS() : ASMInstruction("SUB")
{}

size_t SUB_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The SUB instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 15;

	int32_t registerIdOne = langDef->GetRegisterID<int32_t>(args[0]);
	int32_t registerIdTwo = langDef->GetRegisterID<int32_t>(args[1]);

	CheckRegisterIDInvalid<int32_t, 16, 17, 18>(registerIdOne);

	SerializeToBuffer<int32_t>(buffer, opcode, registerIdOne, registerIdTwo);

	CheckRegisterIDWarning<int32_t, 19, 20, 21>(registerIdOne, sizeof(int32_t) * 3);

	return sizeof(int32_t) * 3;
}