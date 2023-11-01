#include "../../../include/Instructions/TRP_INS/TRP_INS.h"

#include <stdexcept>

#include "../../../include/ASM4380.h"

TRP_INS::TRP_INS() : ASMInstruction("TRP")
{}

size_t TRP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The .TRP instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 21;

	int32_t trapNum = GetImmediateValue<int32_t>(args[0]);

	if (trapNum < 0 || trapNum > 7)
		throw std::runtime_error("Value provided to .TRP instruciton - \"" + std::to_string(trapNum) + "\" - is invalid. Valid traps are 0 - 7");

	SerializeToBuffer<int32_t>(buffer, opcode, trapNum, 0);

	if (trapNum == 0)
		ASM4380::_trapZero = true;

	return sizeof(int32_t) * 3;
}