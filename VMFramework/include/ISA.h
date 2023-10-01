#ifndef ISA_H
#define ISA_H

#include <concepts>

#include <cstdint>
#include <cstddef>

#include "Instruction.h"

namespace VMFramework
{
	template<typename OpCodeType>
	requires std::integral<OpCodeType>
	class ISA
	{
	protected:
		constexpr size_t cexp_setSize;

		Instruction<OpCodeType>[cexp_setSize] m_instructionSet;

	public:
		/// <summary>
		/// Create instance of ISA with the entered set of instructions
		/// </summary>
		/// <param name="instructions">Pointer to array of defined Instructions to populate ISA with</param>
		/// <param name="numInstructions">The number of Instructions in the array</param>
		ISA(Instruction<OpCodeType>* instructions, const size_t& numInstructions);

		~ISA();

		//Do not attempt to copy
		ISA(const ISA&) = delete;
		ISA& operator=(const ISA&) = delete;
		ISA(ISA&&) = delete;
		ISA& operator=(ISA&&) = delete;
	};
}
#endif //!ISA_H
