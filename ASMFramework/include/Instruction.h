#ifndef ASM_INSTRUCTION_H
#define ASM_INSTRUCTION_H

#include <string>

#include "Workpiece.h"
#include "SingletonWrapper.h"

namespace ASMFramework
{
	struct Instruction
	{
	protected:
		Instruction(const std::string& mnemonic);

	public:
		const std::string _mnemonic;

		virtual void Implementation(Workpiece* workpiece) = 0;
	};
}
#endif // !INSTRUCTION_H
