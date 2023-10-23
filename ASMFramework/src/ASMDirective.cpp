#include "../include/ASMDirective.h"

#include <utility>
#include <string>
#include <regex>

namespace ASMFramework
{
	ASMDirective::ASMDirective(std::string&& mnemonic): _mnemonic(std::move(mnemonic))
	{}

	const std::regex ASMDirective::decimalPattern = std::regex(R"delim((^#\d+$))delim", std::regex_constants::ECMAScript);
	const std::regex ASMDirective::hexPattern = std::regex(R"delim((^0x[0-9a-fA-F]+$))delim", std::regex_constants::ECMAScript);
	const std::regex ASMDirective::asciiPattern = std::regex(R"delim((^'.'$)|(^'\\[tnr]'$))delim", std::regex_constants::ECMAScript);
	const std::regex ASMDirective::stringPattern = std::regex(R"delim((^".*?"$))delim", std::regex_constants::ECMAScript);
}