#include "../include/ASMInstruction.h"

#include <utility>

namespace ASMFramework
{
	const std::regex ASMInstruction::registerPattern = std::regex(R"delim((^R\d{1,2}$))delim", std::regex_constants::ECMAScript);
	const std::regex ASMInstruction::decimalPattern = std::regex(R"delim((^#\d+$))delim", std::regex_constants::ECMAScript);
	const std::regex ASMInstruction::hexPattern = std::regex(R"delim((^0x[0-9a-fA-F]+$))delim", std::regex_constants::ECMAScript);
	const std::regex ASMInstruction::asciiPattern = std::regex(R"delim((^'.'$)|(^'\\[tnr]'$))delim", std::regex_constants::ECMAScript);

	ASMInstruction::ASMInstruction(std::string&& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}