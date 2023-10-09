#include "../include/Instruction.h"

#include <utility>

namespace ASMFramework
{
	Instruction::Instruction(const std::string& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}