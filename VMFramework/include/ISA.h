#ifndef ISA_H
#define ISA_H

#include <concepts>

#include <cstdint>
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <string>

#include "Instruction.h"
//#include "Process.h"

constexpr size_t cexp_setSize = 40;

namespace VMFramework
{
	template<typename RegisterType, typename ProcessType>
	class ISA
	{
	protected:
		using InstructionType = Instruction<RegisterType, ProcessType>;

		InstructionType* m_instructionSet[cexp_setSize];

	public:
		/// <summary>
		/// Create instance of ISA with the entered set of instructions
		/// </summary>
		/// <param name="instructions">Pointer to array of defined Instructions to populate ISA with</param>
		/// <param name="numInstructions">The number of Instructions in the array</param>
		ISA(InstructionType* instructions[], const size_t& numInstructions) : m_instructionSet{}
		{
			for (size_t index = 0; index < numInstructions; index++)
			{
				if (instructions[index]->opcode < cexp_setSize && instructions[index]->opcode >= 0)
				{
					m_instructionSet[instructions[index]->opcode] = std::move(instructions[index]);
				}
				else
				{
					throw std::out_of_range("The instructionSet collection has been initialized with " + std::to_string(cexp_setSize) + 
						" spaces. The specified opcode (" + std::to_string(instructions[index]->opcode) +
						") is out of range for the instructionSet collection. Set the cexp_setSize varable to increase the set size if this opcode is correct");
				}
			}
		}

		~ISA()
		{
		}

		InstructionType* operator[](const size_t& index) const
		{
			if (index >= 0 && index < cexp_setSize)
			{
				return m_instructionSet[index];
			}
			else
			{
				throw std::out_of_range("Unknown opcode " + std::to_string(index));
			}
		}

		//Do not attempt to copy
		ISA(const ISA&) = delete;
		ISA& operator=(const ISA&) = delete;
		ISA(ISA&&) = delete;
		ISA& operator=(ISA&&) = delete;
	};
}
#endif //!ISA_H
