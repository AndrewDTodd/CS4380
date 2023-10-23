#include "../include/ASMInstruction.h"

#include <utility>

namespace ASMFramework
{
	ASMInstruction::ASMInstruction(std::string&& mnemonic): _mnemonic(std::move(mnemonic))
	{}

	const std::regex ASMInstruction::registerPattern = std::regex(R"delim((^R\d{1,2}$))delim", std::regex_constants::ECMAScript);
}