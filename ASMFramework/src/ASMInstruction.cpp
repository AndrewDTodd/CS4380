#include "../include/ASMInstruction.h"

#include <utility>

namespace ASMFramework
{
	ASMInstruction::ASMInstruction(const std::string& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}