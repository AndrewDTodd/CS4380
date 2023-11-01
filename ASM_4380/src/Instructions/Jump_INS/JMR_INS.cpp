#include "../../../include/Instructions/Jump_INS/JMR_INS.h"

#include <stdexcept>

JMR_INS::JMR_INS() : ASMInstruction("JMR")
{}

size_t JMR_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The JMR instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 2;
	const std::string& registerMnemonic = args[0];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);

	SerializeToBuffer<int32_t>(buffer, opcode, id, 0);

	if (id > 15)
	{
		switch (id)
		{
		case 16:
			throw Warning("Jumping to PC is kinda redundent, don't you think", sizeof(int32_t) * 3);
			break;

		case 17:
			throw Warning("A jump to SL is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 18:
			throw Warning("A jump to SB is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 19:
			throw Warning("A jump to SP is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 20:
			throw Warning("A jump to FP is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 21:
			throw Warning("A jump to HP is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
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