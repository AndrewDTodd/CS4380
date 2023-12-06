#include "../../../include/Instructions/Stack_INS/PEEK_INS.h"

#include <stdexcept>

PEEK_INS::PEEK_INS() : ASMInstruction("PEEK")
{}

size_t PEEK_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The PEEK instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 42;
	const std::string& registerMnemonic = args[0];

	int32_t id = langDef->GetRegisterID<int32_t>(registerMnemonic);

	SerializeToBuffer<int32_t>(buffer, opcode, id, 0);

	if (id > 15)
	{
		switch (id)
		{
		case 16:
			throw Warning("This is not a valid way to set the PC and will result in a runtime protection fault", sizeof(int32_t) * 3);
			break;

		case 17:
			throw Warning("Setting the SL in this way is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 18:
			throw Warning("Setting the SB in this way is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 19:
			throw Warning("Setting the SP this way is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 20:
			throw Warning("Setting the FP this way is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

		case 21:
			throw Warning("Setting the HP this way is dangerous. Behavior is undefined. Reconsider what you're doing", sizeof(int32_t) * 3);
			break;

#ifdef _DEBUG
		default:
			throw std::logic_error("**Debug logic_error** Somehow LanguageDefinition->GetRegisterID returned a value that we dont handle");
			break;
#endif // _DEBUG
		}

	return sizeof(int32_t) * 3;
}