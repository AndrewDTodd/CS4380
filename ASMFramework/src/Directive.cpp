#include "../include/Directive.h"

#include <utility>

namespace ASMFramework
{
	Directive::Directive(const std::string& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}