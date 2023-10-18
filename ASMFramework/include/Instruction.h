#ifndef ASM_INSTRUCTION_H
#define ASM_INSTRUCTION_H

#include <string>
#include <stdexcept>

#include "Workpiece.h"

namespace ASMFramework
{
	struct Instruction
	{
	protected:
		Instruction(const std::string& mnemonic);

		class NotImplemented : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Assembly Instruction not yet implemented";
			}
		};

	public:
		const std::string _mnemonic;

		virtual void Implementation(const Workpiece* const& workpiece) const = 0;
	};
}
#endif // !INSTRUCTION_H
