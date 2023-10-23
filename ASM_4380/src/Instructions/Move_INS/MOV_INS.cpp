#include "../../../include/Instructions/Move_INS/MOV_INS.h"

#include <stdexcept>
#include <regex>
#include <string>

MOV_INS::MOV_INS() : ASMInstruction("MOV")
{}

size_t MOV_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 2)
		throw std::runtime_error("The .MOV instruction expects two arguments, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 7;

	for (auto& arg : args)
	{
		if (!std::regex_match(arg, registerPattern))
			throw std::runtime_error("Inproperly formatted register mnemonic \"" + arg + "\". Accepted values are R0 - R15");
	}

	int32_t registerIdOne = std::stoi(args[0].substr(1));
	int32_t registerIdTwo = std::stoi(args[1].substr(1));

	if(registerIdOne > 15 || registerIdOne < 0)
		throw std::runtime_error("Invalid register ID. System has no general purpose register with id \"" + std::to_string(registerIdOne) + "\". " + args[0] + 
			" is not a valid register mnemonic. Accepted values are R0 - R15");
	if (registerIdTwo > 15 || registerIdTwo < 0)
		throw std::runtime_error("Invalid register ID. System has no general purpose register with id \"" + std::to_string(registerIdOne) + "\". " + args[1] +
			" is not a valid register mnemonic. Accepted values are R0 - R15");

	SerializeToBuffer<int32_t, int32_t>(opcode, buffer);
	SerializeToBuffer<int32_t, int32_t>(registerIdOne, buffer);
	SerializeToBuffer<int32_t, int32_t>(registerIdTwo, buffer);

	return sizeof(int32_t) * 3;
}