#include "../include/ASMInstruction.h"

#include <utility>

namespace ASMFramework
{
	ASMInstruction::ASMInstruction(std::string&& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}