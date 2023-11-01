#include "../../../include/Instructions/Move_INS/MOV_INS.h"

#include <stdexcept>
#include <regex>
#include <string>

MOV_INS::MOV_INS() : ASMInstruction("MOV")
{}

size_t MOV_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The MOV instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 7;

	int32_t registerIdOne = langDef->GetRegisterID<int32_t>(args[0]);
	int32_t registerIdTwo = langDef->GetRegisterID<int32_t>(args[1]);

	SerializeToBuffer<int32_t>(buffer, opcode, registerIdOne, registerIdTwo);

	return sizeof(int32_t) * 3;
}