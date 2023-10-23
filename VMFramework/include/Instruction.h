#ifndef VM_INSTRUCTION_H
#define VM_INSTRUCTION_H

#include <concepts>

//#include "Process.h"

namespace VMFramework
{
	template<typename GPRegisterType, typename RegisterType, typename ProcessType>
	//requires std::integral<RegisterType> && std::derived_from<ProcessType, VMFramework::Process<GPRegisterType, RegisterType>>
	struct Instruction
	{
	protected:
		Instruction(RegisterType&& code): opcode(code)
		{}

	public:
		/// <summary>
		/// The numeric code associated with this operation
		/// </summary>
		const RegisterType opcode;

		/// <summary>
		/// Pure virtual abstract definition of Instruction's Op method. Deriving types implement this method to define what that Instruction does
		/// </summary>
		/// <param name="executingProcess">Pointer to the Process object that represents the thread of execution executing this Instruction</param>
		virtual void Op(ProcessType* executingProcess) = 0;

		Instruction(const Instruction&) = delete;
		Instruction& operator=(const Instruction&) = delete;
		Instruction(Instruction&&) = delete;
		Instruction& operator=(Instruction&&) = delete;
	};
}
#endif //!INSTRUCTION_H
