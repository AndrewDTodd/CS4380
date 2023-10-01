#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <concepts>

#include "Process.h"

namespace VMFramework
{
	template<typename OpCodeType>
	requires std::integral<OpCodeType>
	struct Instruction
	{
	public:
		/// <summary>
		/// The numeric code associated with this operation
		/// </summary>
		OpCodeType opcode;

		/// <summary>
		/// Pure virtual abstract definition of Instruction's Op method. Deriving types implement this method to define what that Instruction does
		/// </summary>
		/// <param name="executingProcess">Pointer to the Process object that represents the thread of execution executing this Instruction</param>
		virtual void Op(Process* executingProcess) = 0;

		Instruction(const Instruction&) = delete;
		Instruction& operator=(const Instruction&) = delete;
		Instruction(Instruction&&) = delete;
		Instruction& operator=(Instruction&&) = delete;
	};
}
#endif //!INSTRUCTION_H
