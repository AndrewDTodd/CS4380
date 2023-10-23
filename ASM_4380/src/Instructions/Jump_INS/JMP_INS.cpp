#include "../../../include/Instructions/Jump_INS/JMP_INS.h"

#include <stdexcept>
#include <cstdint>

JMP_INS::JMP_INS() : ASMInstruction("JMP")
{}

size_t JMP_INS::Implementation(std::vector<uint8_t>& buffer, ASMFramework::Workpiece* const& workpiece, const std::vector<std::string>& args) const
{
#ifdef _DEBUG
	if (args.size() != 1)
		throw std::runtime_error("The .JMP instruction expects one argument, " + std::to_string(args.size()) + " given");
#endif // _DEBUG

	const int32_t opcode = 1;
	const std::string& argument = args[0];

	try
	{
		uint64_t& address = workpiece->_symbolTable.at(argument);

		SerializeToBuffer<int32_t, int32_t>(opcode, buffer);
		SerializeToBuffer<int32_t, int32_t>(static_cast<int32_t>(address), buffer);

		if (address == 0)
		{
			size_t offset = buffer.size() - sizeof(int32_t);

			workpiece->_unresolvedLabels[argument].push_back(reinterpret_cast<void*>(buffer.data() + offset));
		}

		SerializeToBuffer<int32_t, int32_t>(0, buffer);

		return sizeof(int32_t) * 3;
	}
	//If the label argument of JMP isnt in the symbol table we must assume the assembly contains an invalid label name
	catch (const std::out_of_range& rangeEx)
	{
		throw std::runtime_error("The label argument for JMP - \"" + argument + "\" - is undefined (not contained within the sybol table)");
	}
}