#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <concepts>
#include <type_traits>
#include <stdexcept>
#include <cstdint>
#include <shared_mutex>
#include <memory>
#include <vector>
#include <filesystem>

#include "Pass.h"
#include "Workpiece.h"
#include "LanguageDefinition.h"

namespace ASMFramework
{
	template<typename T>
	concept DerivedFromPass = std::derived_from<T, Pass>;

	class Assembler
	{
	protected:
		const std::vector<const Pass*> m_passes;

		Workpiece* m_workpiece = nullptr;

		std::filesystem::path m_filePath;

		const LanguageDefinition* _languageSpec = nullptr;

		/// <summary>
		/// Assembler base class constructor. Assembler should be treated as abstract. No instances should be made
		/// </summary>
		/// <param name="workpiece">Reference to the Workpiece instance that will be operated upon by teh Assembler's passes</param>
		/// <param name="langDef">Reference to the LanguageDefinition instance used to define the semantics of the Assembly Language the Assembler is being build for</param>
		/// <param name="...pass">Variadic paramater specifying the Pass instances to use for the concrete implementation</param>
		Assembler(Workpiece* workpiece, const LanguageDefinition* langDef, const DerivedFromPass auto*... passes):
			m_workpiece(workpiece),
			_languageSpec(langDef),
			m_passes{passes...}
		{
		}

		/// <summary>
		/// Default destructor is internal. Assembler is abstract
		/// </summary>
		~Assembler();

	public:
		/// <summary>
		/// Initiate the assembly process on the assebmly code in the file at assemblyPath
		/// </summary>
		/// <param name="assemblyPath">String containing the path to the assembly file to process</param>
		/// <exception cref="std::invalid_argument">Thrown if the provided path is invalid</exception>
		virtual void ProcessASM(const char* assemblyPath);

		/// <summary>
		/// Initiate the assembly process on the assebmly code in the file at assemblyPath
		/// </summary>
		/// <param name="assemblyPath">Filesystem path object containing the path information to the assembly code file</param>
		/// <exception cref="std::invalid_argument">Thrown if the provided path is invalid</exception>
		virtual void ProcessASM(std::filesystem::path&& assemblyPath);

		Assembler(const Assembler&) = delete;
		Assembler& operator=(const Assembler&) = delete;
		Assembler(Assembler&&) = delete;
		Assembler& operator=(Assembler&&) = delete;
	};
}
#endif // !ASSEMBER_H
