#include "../include/ASMDirective.h"

#include <utility>

namespace ASMFramework
{
	ASMDirective::ASMDirective(const std::string& mnemonic): _mnemonic(std::move(mnemonic))
	{}
}