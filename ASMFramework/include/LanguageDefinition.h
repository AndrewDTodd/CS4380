#ifndef LANGUAGE_DEFINITION_H
#define LANGUAGE_DEFINITION_H

#include <unordered_map>
#include <unordered_set>

#include <string>

#include <memory>

#include "Directive.h"
#include "Instruction.h"

template<typename T>
concept DerivedFromDirective = std::derived_from<T, ASMFramework::Directive>;

template<typename T>
concept DerivedFromInstruction = std::derived_from<T, ASMFramework::Instruction>;

template<typename T>
concept StringType = std::is_same_v<T, std::string>;

namespace ASMFramework
{
	class LanguageDefinition
	{
	protected:
		const std::unordered_map<std::string, const Directive*> m_languageDirectives;

		const std::unordered_map<std::string, const Instruction*> m_languageInstructions;

		const std::unordered_set<std::string> m_reservedKeywords;

		LanguageDefinition(const DerivedFromDirective auto&... directive, const DerivedFromInstruction auto&... instruction, std::string&& keyword...);
		~LanguageDefinition();

	public:
		/// <summary>
		/// Get a pointer to the directive with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the Directive under (directive mnemonic)</param>
		/// <returns>Pointer to the Directive if found</returns>
		/// <exception cref="std::out_of_range">If the key is not found an out_of_range exception is thrown</exception>
		const Directive* GetDirective(const std::string& key) const;

		/// <summary>
		/// Get a pointer to the directive with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the Directive under (directive mnemonic)</param>
		/// <param name="out_directive">A reference to a pointer for a Directive, to point to the located Directive if one is found. nullptr otherewise</param>
		/// <returns>True if a Directive was found under the provided key</returns>
		bool TryGetDirective(const std::string& key, const Directive*& out_directive) const;

		/// <summary>
		/// Deturmine if there is a directive with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the Directive under (directive mnemonic)</param>
		/// <returns>True if a Directive was found under the provided key</returns>
		bool ContainsDirective(const std::string& key) const;

		/// <summary>
		/// Get a pointer to the instruction with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the Instruction under (directive mnemonic)</param>
		/// <returns>Pointer to the Instruction if found</returns>
		/// <exception cref="std::out_of_range">If the key is not found an out_of_range exception is thrown</exception>
		const Instruction* GetInstruction(const std::string& key) const;

		/// <summary>
		/// Get a pointer to the instruction with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the Instruction under (directive mnemonic)</param>
		/// <param name="out_instruction">A reference to a pointer for a Instruction, to point to the located Instruction if one is found. nullptr otherewise</param>
		/// <returns>True if a Instruction was found under the provided key</returns>
		bool TryGetInstruction(const std::string& key, const Instruction*& out_instruction) const;

		/// <summary>
		/// Deturmine if there is a instruction with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the Instruction under (directive mnemonic)</param>
		/// <returns>True if a Instruction was found under the provided key</returns>
		bool ContainsInstruction(const std::string& key) const;

		LanguageDefinition(const LanguageDefinition&) = delete;
		LanguageDefinition& operator=(const LanguageDefinition&) = delete;
		LanguageDefinition(LanguageDefinition&&) = delete;
		LanguageDefinition& operator=(LanguageDefinition&&) = delete;
	};
}
#endif // !LANGUAGE_DEFINITION_H
