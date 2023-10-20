#ifndef ASM_INSTRUCTION_H
#define ASM_INSTRUCTION_H

#include <string>
#include <stdexcept>

#include "Workpiece.h"

namespace ASMFramework
{
	struct ASMInstruction
	{
	protected:
		ASMInstruction(const std::string& mnemonic);

		class NotImplemented : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Assembly ASMInstruction not yet implemented";
			}
		};

	public:
		const std::string _mnemonic;

		virtual void Implementation(const Workpiece* const& workpiece) const = 0;
	};
}
#endif // !INSTRUCTION_H
