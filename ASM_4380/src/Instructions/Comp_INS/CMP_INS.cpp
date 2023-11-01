#include "../../../include/Instructions/Comp_INS/CMP_INS.h"

#include <stdexcept>

CMP_INS::CMP_INS() : ASMInstruction("CMP")
{}

size_t CMP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The CMP instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 20;

	int32_t registerIdOne = langDef->GetRegisterID<int32_t>(args[0]);
	int32_t registerIdTwo = langDef->GetRegisterID<int32_t>(args[1]);

	if (registerIdOne > 15)
		throw std::runtime_error("You may not set the value of special registers this way. \"" + args[0] + "\" is not valid in this context. R0 - R15 are valid");

	SerializeToBuffer<int32_t>(buffer, opcode, registerIdOne, registerIdTwo);

	if (registerIdTwo > 15)
	{
		switch (registerIdTwo)
		{
		case 16:
			throw Warning("The PC should always be greater than 0. The use of PC here is probably not correct", sizeof(int32_t) * 3);
			break;

		case 17:
			throw Warning("The SL should always be greater than 0. The use of SL here is probably not correct", sizeof(int32_t) * 3);
			break;

		case 18:
			throw Warning("The SB should always be greater than 0. The use of SB here is probably not correct", sizeof(int32_t) * 3);
			break;

		case 19:
			throw Warning("The SP should always be greater than 0. The use of SP here is probably not correct", sizeof(int32_t) * 3);
			break;

		case 20:
			throw Warning("The FP should always be greater than 0. The use of FP here is probably not correct", sizeof(int32_t) * 3);
			break;

		case 21:
			throw Warning("The HP should always be greater than 0. The use of HP here is probably not correct", sizeof(int32_t) * 3);
			break;

#ifdef _DEBUG
		default:
			throw std::logic_error("**Debug logic_error** Somehow LanguageDefinition->GetRegisterID returned a value that we dont handle");
			break;
#endif // _DEBUG
		}
	}

	return sizeof(int32_t) * 3;
}