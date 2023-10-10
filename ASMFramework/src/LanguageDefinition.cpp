#include "../include/LanguageDefinition.h"

#include <utility>
#include <string>
#include <memory>

#include "../include/Directive.h"
#include "../include/Instruction.h"

namespace ASMFramework
{
	LanguageDefinition::LanguageDefinition(const DerivedFromDirective auto&... directive, const DerivedFromInstruction auto&... instruction)
	{
		(m_languageDirectives.emplace(directive._mnemonic, &directive), ...);
		(m_languageDirectives.emplace(instruction._mnemonic, &instruction), ...);
	}
	LanguageDefinition::~LanguageDefinition()
	{
	}

	const Directive* LanguageDefinition::GetDirective(const std::string& key) const
	{
		return m_languageDirectives.at(key);
	}

	bool LanguageDefinition::TryGetDirective(const std::string& key, const Directive*& out_directive) const
	{
		auto itr = m_languageDirectives.find(key);

		if (itr != m_languageDirectives.end())
		{
			out_directive = (itr->second);

			return true;
		}

		out_directive = nullptr;

		return false;
	}

	bool LanguageDefinition::ContainsDirective(const std::string& key) const
	{
		return m_languageDirectives.find(key) != m_languageDirectives.end();
	}

	const Instruction* LanguageDefinition::GetInstruction(const std::string& key) const
	{
		return m_languageInstructions.at(key);
	}

	bool LanguageDefinition::TryGetInstruction(const std::string& key, const Instruction*& out_instruction) const
	{
		auto itr = m_languageInstructions.find(key);

		if (itr != m_languageInstructions.end())
		{
			out_instruction = (itr->second);

			return true;
		}

		out_instruction = nullptr;

		return false;
	}

	bool LanguageDefinition::ContainsInstruction(const std::string& key) const
	{
		return m_languageInstructions.find(key) != m_languageInstructions.end();
	}
}