#ifndef PASS_H
#define PASS_H

#include <fstream>

#include <memory>

#include "Workpiece.h"
#include "LanguageDefinition.h"

namespace ASMFramework
{
	class Pass
	{
	public:
		virtual void Execute(const Workpiece* const& workpiece, const std::unique_ptr<const std::ifstream>& fileStream, const LanguageDefinition* const& langDef) const = 0;
	};
}
#endif // !PASS_H
