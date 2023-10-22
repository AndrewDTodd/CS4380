#include "../include/ASMDirective.h"

#include <utility>

namespace ASMFramework
{
	ASMDirective::ASMDirective(std::string&& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}