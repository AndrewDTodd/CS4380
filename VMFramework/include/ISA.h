#ifndef ISA_H
#define ISA_H

#include <concepts>

#include <cstdint>
#include <cstddef>

#include "Instruction.h"
//#include "Process.h"

constexpr size_t cexp_setSize = 22;

namespace VMFramework
{
	template<typename GPRegisterType, typename RegisterType, typename ProcessType>
	//requires std::integral<RegisterType> && std::derived_from<ProcessType, VMFramework::Process<GPRegisterType, RegisterType>>
	class ISA
	{
	protected:
		using InstructionType = Instruction<GPRegisterType, GPRegisterType, ProcessType>;

		InstructionType* m_instructionSet[cexp_setSize];

	public:
		/// <summary>
		/// Create instance of ISA with the entered set of instructions
		/// </summary>
		/// <param name="instructions">Pointer to array of defined Instructions to populate ISA with</param>
		/// <param name="numInstructions">The number of Instructions in the array</param>
		ISA(InstructionType* instructions[], const size_t& numInstructions)
		{
			for (size_t index = 0; index < numInstructions; index++)
			{
				m_instructionSet[instructions[index].opcode] = std::move(instructions[index]);
			}
		}

		~ISA()
		{
		}

		//Do not attempt to copy
		ISA(const ISA&) = delete;
		ISA& operator=(const ISA&) = delete;
		ISA(ISA&&) = delete;
		ISA& operator=(ISA&&) = delete;
	};
}
#endif //!ISA_H
