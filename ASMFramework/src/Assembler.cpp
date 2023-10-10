#include "../include/Assembler.h"

#include <stdexcept>

#include <cstdint>

#include <shared_mutex>
#include <mutex>

#include <memory>

#include <vector>

#include <iostream>

#include <utility>


#include "Workpiece.h"
#include "Pass.h"
#include "LanguageDefinition.h"

namespace ASMFramework
{
	Assembler::Assembler(const DerivedFromPass auto&... pass, const Workpiece& workpiece, const LanguageDefinition& langDef): m_workpiece(&workpiece), _languageSpec(&langDef)
	{
		(m_passes.emplace_back(&pass), ...);
	}
	Assembler::~Assembler()
	{
	}

	void Assembler::ProcessASM(const char* assemblyPath)
	{
		std::ifstream file(assemblyPath);

		if (!file.is_open())
		{
			throw std::invalid_argument("Unable to open file at path: " + std::string(assemblyPath));
		}

		for (auto& pass : m_passes)
		{
			pass->Execute(m_workpiece, m_fileStream, _languageSpec);
		}
	}
}