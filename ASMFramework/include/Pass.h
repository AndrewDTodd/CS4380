#ifndef PASS_H
#define PASS_H

#include <filesystem>

#include <memory>

#include "Workpiece.h"
#include "LanguageDefinition.h"
#include "ASMDirective.h"
#include "ASMInstruction.h"

namespace ASMFramework
{
	class Pass
	{
	public:
		virtual void Execute(Workpiece* const& workpiece, const std::filesystem::path& filePath, const LanguageDefinition* const& langDef) const = 0;
	};
}
#endif // !PASS_H
