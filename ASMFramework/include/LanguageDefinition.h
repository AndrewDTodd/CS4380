#ifndef LANGUAGE_DEFINITION_H
#define LANGUAGE_DEFINITION_H

#include <unordered_map>
#include <unordered_set>

#include <string>
#include <stdexcept>
#include <memory>
#include <cstdint>
#include <concepts>
#include <limits>

namespace ASMFramework
{
	struct ASMDirective;
	struct ASMInstruction;
}

template<typename T>
concept DerivedFromDirective = std::derived_from<T, ASMFramework::ASMDirective>;

template<typename T>
concept DerivedFromInstruction = std::derived_from<T, ASMFramework::ASMInstruction>;

template<typename T>
concept StringType = std::is_same_v<T, std::string>;

namespace ASMFramework
{
	class LanguageDefinition
	{
	protected:
		const std::unordered_map<std::string, const ASMFramework::ASMDirective*> m_languageDirectives;

		const std::unordered_map<std::string, const ASMFramework::ASMInstruction*> m_languageInstructions;

		const std::unordered_set<std::string> m_reservedKeywords;

		const std::unordered_map<std::string, const uint8_t> m_registerMnemonics;

		/// <summary>
		/// Default constructor is private, LanguageDefinition is abstract. Internal use only
		/// </summary>
		LanguageDefinition();

		/// <summary>
		/// Destructor is private, LanguageDefinition is abstract. Internal use only
		/// </summary>
		~LanguageDefinition();

		/// <summary>
		/// Deriving type must call this method to initiaize the Directives for the LanguageDefinition
		/// </summary>
		/// <param name="...directives">Parameter pack (variable number) of ASMDirective instances to load into LanguageDefinition</param>
		void SetDirectives(const DerivedFromDirective auto&... directives)
		{
			std::unordered_map<std::string, const ASMFramework::ASMDirective*>& non_const_directives =
				const_cast<std::unordered_map<std::string, const ASMFramework::ASMDirective*>&>(m_languageDirectives);

			(non_const_directives.emplace(directives._mnemonic, &directives), ...);
		}

		/// <summary>
		/// Deriving type must call this method to initiaize the Instructions for the LanguageDefinition
		/// </summary>
		/// <param name="...instructions">Parameter pack (variable number) of ASMInstruction instances to load into LanguageDefinition</param>
		void SetInstructions(const DerivedFromInstruction auto&... instructions)
		{
			std::unordered_map<std::string, const ASMFramework::ASMInstruction*>& non_const_instructions =
				const_cast<std::unordered_map<std::string, const ASMFramework::ASMInstruction*>&>(m_languageInstructions);

			(non_const_instructions.emplace(instructions._mnemonic, &instructions), ...);
		}

		/// <summary>
		/// Deriving type must call this method to initiaize the Keywords for the LanguageDefinition
		/// </summary>
		/// <param name="...keywords">Parameter pack (variable number) of Keywords (strings) to load into LanguageDefinition</param>
		void SetKeywords(StringType auto&&... keywords)
		{
			std::unordered_set<std::string>& non_const_keywords =
				const_cast<std::unordered_set<std::string>&>(m_reservedKeywords);

			(non_const_keywords.emplace(std::forward<std::string&&>(keywords)), ...);
		}

		/// <summary>
		/// Deriving type must call this method to initiaize the register mnemonics for the LanguageDefinition
		/// </summary>
		/// <param name="...mnemonics">Parameter pack (variable number) of Keywords (strings) to load into LanguageDefinition</param>
		void SetRegisterMnemonics(StringType auto&&... mnemonics)
		{
			static_assert(sizeof...(mnemonics) <= 255, "System only supports up to 255 registers");

			std::unordered_map<std::string, const uint8_t>& non_const_regMnemonics =
				const_cast<std::unordered_map<std::string, const uint8_t>&>(m_registerMnemonics);

			uint8_t i = 0;

			(non_const_regMnemonics.emplace(std::forward<std::string&&>(mnemonics), i++), ...);
		}

	public:
		/// <summary>
		/// Get a pointer to the directive with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the ASMDirective under (directive mnemonic)</param>
		/// <returns>Pointer to the ASMDirective if found</returns>
		/// <exception cref="std::out_of_range">If the key is not found an out_of_range exception is thrown</exception>
		inline const ASMFramework::ASMDirective* GetDirective(const std::string& key) const
		{
			return m_languageDirectives.at(key);
		}

		/// <summary>
		/// Get a pointer to the directive with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the ASMDirective under (directive mnemonic)</param>
		/// <param name="out_directive">A reference to a pointer for a ASMDirective, to point to the located ASMDirective if one is found. nullptr otherewise</param>
		/// <returns>True if a ASMDirective was found under the provided key</returns>
		inline bool TryGetDirective(const std::string& key, const ASMFramework::ASMDirective*& out_directive) const
		{
			try
			{
				out_directive = m_languageDirectives.at(key);

				return true;
			}
			catch (const std::out_of_range& rngEX)
			{
				out_directive = nullptr;

				return false;
			}
		}

		/// <summary>
		/// Deturmine if there is a directive with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the ASMDirective under (directive mnemonic)</param>
		/// <returns>True if a ASMDirective was found under the provided key</returns>
		inline bool ContainsDirective(const std::string& key) const
		{
			return m_languageDirectives.contains(key);
		}

		/// <summary>
		/// Get a pointer to the instruction with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the ASMInstruction under (directive mnemonic)</param>
		/// <returns>Pointer to the ASMInstruction if found</returns>
		/// <exception cref="std::out_of_range">If the key is not found an out_of_range exception is thrown</exception>
		inline const ASMFramework::ASMInstruction* GetInstruction(const std::string& key) const
		{
			return m_languageInstructions.at(key);
		}

		/// <summary>
		/// Get a pointer to the instruction with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the ASMInstruction under (directive mnemonic)</param>
		/// <param name="out_instruction">A reference to a pointer for a ASMInstruction, to point to the located ASMInstruction if one is found. nullptr otherewise</param>
		/// <returns>True if a ASMInstruction was found under the provided key</returns>
		inline bool TryGetInstruction(const std::string& key, const ASMFramework::ASMInstruction*& out_instruction) const
		{
			try
			{
				out_instruction = m_languageInstructions.at(key);

				return true;
			}
			catch (const std::out_of_range& rngEx)
			{
				out_instruction = nullptr;

				return false;
			}
		}

		/// <summary>
		/// Deturmine if there is a instruction with the provided key (mnemonic)
		/// </summary>
		/// <param name="key">The key to search the ASMInstruction under (directive mnemonic)</param>
		/// <returns>True if a ASMInstruction was found under the provided key</returns>
		inline bool ContainsInstruction(const std::string& key) const
		{
			return m_languageInstructions.contains(key);
		}

		/// <summary>
		/// Deturmine if the language has a reserved keyword with the provided key
		/// </summary>
		/// <param name="key">The key to search the Keyword under</param>
		/// <returns>True if the Keyword was found, false otherwise</returns>
		inline bool ContainsKeyword(const std::string& key) const
		{
			return m_reservedKeywords.contains(key) || m_registerMnemonics.contains(key);
		}

		/// <summary>
		/// Returns the ID of the register represented byt the supplied mnemonic
		/// </summary>
		/// <typeparam name="TargetType">The integral type to return the ID casted too</typeparam>
		/// <param name="mnemonic">The key to search for the ID under</param>
		/// <returns>The ID of the register corresponding to the supplied mnemonic, if one exists</returns>
		/// <exception cref="std::out_of_range Thrown if there is no register with the supplied mnemonic"/>
		template<std::integral TargetType>
		inline TargetType GetRegisterID(const std::string& mnemonic) const
		{
			return static_cast<TargetType>(m_registerMnemonics.at(mnemonic));
		}


		LanguageDefinition(const LanguageDefinition&) = delete;
		LanguageDefinition& operator=(const LanguageDefinition&) = delete;
		LanguageDefinition(LanguageDefinition&&) = delete;
		LanguageDefinition& operator=(LanguageDefinition&&) = delete;
	};
}
#endif // !LANGUAGE_DEFINITION_H
