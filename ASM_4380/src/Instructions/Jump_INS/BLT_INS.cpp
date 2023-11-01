#include "../../../include/Instructions/Jump_INS/BLT_INS.h"

#include <stdexcept>

BLT_INS::BLT_INS() : ASMInstruction("BLT")
{}

size_t BLT_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The BLT instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 5;
	const std::string& registerMnemonic = args[0];
	const std::string& labelName = args[1];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);
	uint64_t& offset = ASMFramework::ASMInstruction::GetLabelOffset(labelName, workpiece);

	SerializeToBuffer<int32_t>(buffer, opcode, id, static_cast<int32_t>(offset));

	if (offset == 0)
		AddUnresolvedLabel<int32_t>(labelName, buffer, workpiece);

	if (id > 15)
	{
		switch (id)
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