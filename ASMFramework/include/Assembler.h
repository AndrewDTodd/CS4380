#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <concepts>
#include <type_traits>

#include <stdexcept>

#include <cstdint>

#include <shared_mutex>

#include <memory>

#include <vector>

#include <fstream>

#include "Pass.h"
#include "Workpiece.h"

namespace ASMFramework
{
	template<typename T>
	concept DerivedFromPass = std::derived_from<T, Pass>;

	class Assembler
	{
	protected:
		const std::vector<Pass*> m_passes;

		Workpiece* m_workpiece = nullptr;

		const std::ifstream* m_fileStream = nullptr;

		Assembler(const DerivedFromPass auto&... passes, const Workpiece& workpiece);
		~Assembler();

	public:
		/// <summary>
		/// Called to set the Assembler to assembling the assembly code in the file at the assemblyPath location
		/// </summary>
		/// <param name="assemblyPath">String containing the path to the assembly file to process</param>
		/// <exeption cref="std::invalid_argument">Thrown if the file at assemblyPath cannot be opened</exeption>
		virtual void ProcessASM(const char* assemblyPath);

		Assembler(const Assembler&) = delete;
		Assembler& operator=(const Assembler&) = delete;
		Assembler(Assembler&&) = delete;
		Assembler& operator=(Assembler&&) = delete;
	};
}
#endif // !ASSEMBER_H
